// Copyright 2018 Gribak Jaroslav

#include <inttypes.h>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

class Set {
 public:
    explicit Set(const vector<int64_t>& v);
    Set() = default;
    void Add(int64_t value);
    bool Contains(int64_t value);
    void Remove(int64_t value);
    vector<int64_t> Data() const;
    Set Union(const Set& set) const;
    Set Intersection(const Set& set) const;
    Set Difference(const Set& set) const;
    Set SymmetricDifference(const Set& set) const;
 private:
    vector<int64_t> data;
};

Set::Set(const vector<int64_t>& v) {
  for (auto it = v.begin(); it != v.end(); it++)
    Add(*it);
}

bool Set::Contains(int64_t value) {
  for (auto it = data.begin(); it != data.end(); it++) {
    if (*it == value)
      return true;
  }
  return false;
}

void Set::Add(int64_t value) {
  if (!Contains(value))
    data.push_back(value);
}

void Set::Remove(int64_t value) {
  for (auto it = data.begin(); it != data.end(); it++) {
    if (*it == value) {
      *it = *(data.end() - 1);
      data.pop_back();
      break;
    }
  }
}

vector<int64_t> Set::Data() const {
  return data;
}

Set Set::Union(const Set& set) const {
  vector<int64_t> v = set.Data();
  Set temp(Data());
  for (auto it = v.begin(); it != v.end(); it++) {
    temp.Add(*it);
  }
  return temp;
}

Set Set::Intersection(const Set& set) const {
  vector<int64_t> result;
  vector<int64_t> sdata = set.Data();
  for (auto it = data.begin(); it != data.end(); it++) {
    for (auto it2 = sdata.begin(); it2 != sdata.end(); it2++) {
      if (*it == *it2) {
        result.push_back(*it);
        break;
      }
    }
  }
  return Set(result);
}

Set Set::Difference(const Set& set) const {
  vector<int64_t> result;
  vector<int64_t> sdata = set.Data();
  for (auto it = data.begin(); it != data.end(); it++) {
    bool is_unic = true;
    for (auto it2 = sdata.begin(); it2 != sdata.end(); it2++) {
      if (*it == *it2) {
        is_unic = false;
        break;
      }
    }

    if (is_unic)
      result.push_back(*it);
  }
  return Set(result);
}

Set Set::SymmetricDifference(const Set& set) const {
  vector<int64_t> result;
  vector<int64_t> sdata = set.Data();
  for (auto it = data.begin(); it != data.end(); it++) {
    bool is_unic = true;
    for (auto it2 = sdata.begin(); it2 != sdata.end(); it2++) {
      if (*it == *it2) {
        is_unic = false;
        break;
      }
    }

    if (is_unic)
      result.push_back(*it);
  }

  for (auto it = sdata.begin(); it != sdata.end(); it++) {
    bool is_unic = true;
    for (auto it2 = data.begin(); it2 != data.end(); it2++) {
      if (*it == *it2) {
        is_unic = false;
        break;
      }
    }

    if (is_unic)
      result.push_back(*it);
  }
  return Set(result);
}
