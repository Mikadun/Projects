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

bool Compare(const GameObject& a, const GameObject& b) {
    return a.id > b.id;
}

bool operator>(const GameObject& a, const GameObject& b) {
  return a.id > b.id;
}

template<class T, template<class> class Compare>
class DereferenceCompare {
 public:
    bool operator()(const T* const a, const T* const b) {
      return comp(*a, *b);
    }
 private:
    Compare<T> comp;
};

using TPos = pair<size_t, size_t>;
using TVec = vector<GameObject>;
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
    // map<TPos, TVec> by_pos;
    map<string, TSet> by_name;
};

void GameDatabase::Insert(ObjectId id, string name, size_t x, size_t y) {
  GameObject temp = {id, name, x, y};
  if (data.find(id) != data.end())
    Remove(id);
  data.insert(make_pair(id, temp));
  by_name[name].insert(&data[id]);
  /*
  TPos pos = make_pair(x, y);
  by_pos[pos].push_back(temp);
  */
}

void GameDatabase::Remove(ObjectId id) {
  auto it = data.find(id);
  if (it != data.end()) {
    GameObject obj = it->second;
    by_name[obj.name].erase(&obj);
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

/*
vector<GameObject> GameDatabase::DataByPosition(size_t x, size_t y) const {
  vector<GameObject> result;
  TPos pos = make_pair(x, y);
  if (by_pos.find(pos) == by_pos.end())
    return result;
  TVec container = by_pos.find(pos)->second;
  for (auto it = container.begin(); it != container.end(); it++) {
    auto in_data = data.find(it->id);
    GameObject obj = in_data->second;
    if (in_data != data.end() && obj.x == x && obj.y == y) {
      result.push_back(obj);
    }
  }
  std::sort(result.begin(), result.end(), Compare);
  return result;
}
*/

///*
vector<GameObject> GameDatabase::DataByPosition(size_t x, size_t y) const {
  vector<GameObject> result;
  for (auto it = data.begin(); it != data.end(); it++) {
    if (it->second.x == x && it->second.y == y)
      result.push_back(it->second);
  }
  std::sort(result.begin(), result.end(), Compare);
  return result;
}
//*/

vector<GameObject> GameDatabase::Data() const {
  vector<GameObject> result;
  for (auto it = data.begin(); it != data.end(); it++)
    result.push_back(it->second);
  return result;
}
