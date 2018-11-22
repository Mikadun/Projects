// Copyright 2018 Gribak Jaroslav

#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <iterator>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

using std::string;
using std::set;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::unordered_map;

bool operator>(const GameObject& a, const GameObject& b) {
  return a.id > b.id;
}

bool operator<(const GameObject& a, const GameObject& b) {
  return a.id < b.id;
}

using TPos = pair<size_t, size_t>;
using TVec = vector<GameObject>;

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
    map<TPos, TVec> by_pos;
    unordered_map<string, TVec> by_name;
};

void GameDatabase::Insert(ObjectId id, string name, size_t x, size_t y) {
  GameObject temp = {id, name, x, y};
  data.insert_or_assign(id, temp);
  by_name[name].push_back(temp);
  by_pos[TPos(x, y)].push_back(temp);
}

void GameDatabase::Remove(ObjectId id) {
  auto obj = data.find(id);
  if (obj != data.end()) {
    data.erase(obj);
  }
}

pair<GameObject, bool> GameDatabase::DataById(ObjectId id) const {
  auto result = data.find(id);
  return make_pair(result->second, result != data.end());
}

vector<GameObject> GameDatabase::DataByName(string name) const {
  vector<GameObject> result;
  TVec container = by_name.find(name)->second;
  for (auto it = container.begin(); it != container.end(); it++) {
    auto in_data = data.find(it->id);
    if (in_data != data.end() && in_data->second.name == name) {
      result.push_back(*it);
    }
  }

  std::sort(result.begin(), result.end());
  return result;
}


vector<GameObject> GameDatabase::DataByPosition(size_t x, size_t y) const {
  vector<GameObject> result;
  TPos pos(x, y);
  TVec container = by_pos.find(pos)->second;
  for (auto it = container.begin(); it != container.end(); it++) {
    auto in_data = data.find(it->id);
    GameObject obj = in_data->second;
    if (in_data != data.end() && obj.x == x && obj.y == y) {
      result.push_back(*it);
    }
  }
  std::sort(result.begin(), result.end());
  return result;
}

vector<GameObject> GameDatabase::Data() const {
  vector<GameObject> result;
  for (auto it = data.begin(); it != data.end(); it++)
    result.push_back(it->second);
  return result;
}
