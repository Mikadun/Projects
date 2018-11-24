// Copyright 2018 Gribak Jaroslav

#include <map>
#include <set>
#include <string>
#include <iterator>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

using std::string;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::set;

bool operator>(const GameObject& a, const GameObject& b) {
  return a.id > b.id;
}

template<class T, template<class> class Compare>
class DereferenceCompare {
 public:
    bool operator()(const T* const a, const T* const b) const {
      return comp(*a, *b);
    }
 private:
    Compare<T> comp;
};

using TPos = pair<size_t, size_t>;
using TSet = set<GameObject*, DereferenceCompare<GameObject, std::greater>>;

class GameDatabase {
 public:
    GameDatabase() = default;

    void Insert(ObjectId id, string name, size_t x, size_t y);
    void Remove(ObjectId id);
    pair<GameObject, bool> DataById(ObjectId id) const;
    vector<GameObject> DataByName(string name) const;
    vector<GameObject> DataByPosition(size_t x, size_t y) const;
    vector<GameObject> Data() const;

 private:
    map<ObjectId, GameObject, std::greater<ObjectId>> data;
    map<TPos, TSet> by_pos;
    map<string, TSet> by_name;
};

void GameDatabase::Insert(ObjectId id, string name, size_t x, size_t y) {
  GameObject temp = {id, name, x, y};
  if (data.find(id) != data.end())
    Remove(id);
  data.insert(make_pair(id, temp));
  by_name[name].insert(&data[id]);
  TPos pos = make_pair(x, y);
  by_pos[pos].insert(&data[id]);
}

void GameDatabase::Remove(ObjectId id) {
  auto it = data.find(id);
  if (it != data.end()) {
    GameObject obj = it->second;
    by_name[obj.name].erase(&obj);
    TPos pos = make_pair(obj.x, obj.y);
    by_pos[pos].erase(&obj);
    data.erase(it);
  }
}

pair<GameObject, bool> GameDatabase::DataById(ObjectId id) const {
  auto result = data.find(id);
  return make_pair(result->second, result != data.end());
}

vector<GameObject> GameDatabase::DataByName(string name) const {
  vector<GameObject> result;
  if (by_name.find(name) != by_name.end()) {
    TSet container = by_name.find(name)->second;
    for (auto it = container.begin(); it != container.end(); it++) {
      result.push_back(**it);
    }
  }
  return result;
}

vector<GameObject> GameDatabase::DataByPosition(size_t x, size_t y) const {
  vector<GameObject> result;
  TPos pos = make_pair(x, y);
  if (by_pos.find(pos) != by_pos.end()) {
    TSet container = by_pos.find(pos)->second;
    for (auto it = container.begin(); it != container.end(); it++) {
      result.push_back(**it);
    }
  }
  return result;
}

vector<GameObject> GameDatabase::Data() const {
  vector<GameObject> result;
  for (auto it = data.begin(); it != data.end(); it++)
    result.push_back(it->second);
  return result;
}
