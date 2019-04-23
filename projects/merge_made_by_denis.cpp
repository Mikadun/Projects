#include <fstream>
#include <iostream>
#include <type_traits>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <utility>

enum TYPE {NON, MAP, SET, MMAP, MSET};

template<typename T, typename ... Types>
struct is_type {
    static constexpr TYPE value = NON;
};

// is_type
// ========
template<>
struct is_type<int> {
    static constexpr TYPE value = NON;
};

// is_deque
// ========
template<typename ... Types>
struct is_type<std::deque<Types...>> {
    static constexpr TYPE value = NON;
};

// is_forward_list
// ===============
template<typename ... Types>
struct is_type<std::forward_list<Types...>> {
    static constexpr TYPE value = NON;
};

// list
// ====
template<typename ... Types>
struct is_type<std::list<Types...>> {
    static constexpr TYPE value = NON;
};

// is_vector
// ======
template<typename ... Types>
struct is_type<std::vector<Types...>> {
    static constexpr TYPE value = NON;
};

// map
// ===
template<typename ... Types>
struct is_type<std::map<Types...>> {
    static constexpr TYPE value = MAP;
};

// set
// ===
template<typename ... Types>
struct is_type<std::set<Types...>> {
    static constexpr TYPE value = SET;
};

// unordered_map
// =============
template<typename ... Types>
struct is_type<std::unordered_map<Types...>> {
    static constexpr TYPE value = MAP;
};

// unordered_set
// =============
template<typename ... Types>
struct is_type<std::unordered_set<Types...>> {
    static constexpr TYPE value = SET;
};

// unordered_multiset
// =============
template<typename ... Types>
struct is_type<std::unordered_multiset<Types...>> {
    static constexpr TYPE value = MSET;
};

// unordered_multimap
// =============
template<typename ... Types>
struct is_type<std::unordered_multimap<Types...>> {
    static constexpr TYPE value = MMAP;
};

// multiset
// =============
template<typename ... Types>
struct is_type<std::multiset<Types...>> {
    static constexpr TYPE value = MSET;
};

// multimap
// =============
template<typename ... Types>
struct is_type<std::multimap<Types...>> {
    static constexpr TYPE value = MMAP;
};

// is_container
// ============
template <typename T>
struct is_container {
  static constexpr TYPE value = is_type<T>::value;
};

// check_type
// ============
template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == SET
  && is_container<C2>::value == SET, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == MAP
  && is_container<C2>::value == MAP, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == MMAP
  && is_container<C2>::value == MMAP, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == MMAP
  && is_container<C2>::value == MAP, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == MSET
  && is_container<C2>::value == MSET, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <is_container<C1>::value == MSET
  && is_container<C2>::value == SET, bool>::type
check_type(C1* c1, const C2& c2) {
  return true;
}

// check_elem_type
// ============
template <typename T>
struct is_pair2 {
    static constexpr bool value = false;
    typedef T value_type;
};

template<typename T1, typename T2>
struct is_pair2<std::pair<T1, T2>> {
    static constexpr bool value = true;
    typedef T2 value_type;
};

template <typename T>
struct is_pair1 {
    static constexpr bool value = false;
    typedef T value_type;
};

template<typename T1, typename T2>
struct is_pair1<std::pair<T1, T2>> {
    static constexpr bool value = true;
    typedef T1 value_type;
};

// MAJOR
// ============
template<class C1, class C2>
typename std::enable_if
  <(is_container<C1>::value == MSET
  && is_container<C2>::value == SET)
  || (is_container<C1>::value == MSET
  && is_container<C2>::value == MSET)
  || (is_container<C1>::value == MMAP
  && is_container<C2>::value == MAP)
  || (is_container<C1>::value == MMAP
  && is_container<C2>::value == MMAP)
  || (is_container<C1>::value == SET
  && is_container<C2>::value == SET)
  || (is_container<C1>::value == MAP
  && is_container<C2>::value == MAP), bool>::type
MergeAssociative(C1* c1, const C2& c2) {
  typename C1::value_type c1TopElementType;
  typename C2::value_type c2TopElementType;

  typename std::remove_cv<typename is_pair1
    <decltype(c1TopElementType)>::value_type>::type c1DeepType1;
  typename std::remove_cv<typename is_pair1
    <decltype(c2TopElementType)>::value_type>::type c2DeepType1;
  typename std::remove_cv<typename is_pair2
    <decltype(c1TopElementType)>::value_type>::type c1DeepType2;
  typename std::remove_cv<typename is_pair2
    <decltype(c2TopElementType)>::value_type>::type c2DeepType2;

  if (std::is_same<decltype(c1DeepType1), decltype(c2DeepType1)>()
    && std::is_same<decltype(c1DeepType2), decltype(c2DeepType2)>()) {
      for (auto e : c2) {
          c1->insert(e);
      }
      return false;
    }
  return true;
}

template<class C1, class C2>
typename std::enable_if
  <!((is_container<C1>::value == MSET
  && is_container<C2>::value == SET)
  || (is_container<C1>::value == MSET
  && is_container<C2>::value == MSET)
  || (is_container<C1>::value == MMAP
  && is_container<C2>::value == MAP)
  || (is_container<C1>::value == MMAP
  && is_container<C2>::value == MMAP)
  || (is_container<C1>::value == SET
  && is_container<C2>::value == SET)
  || (is_container<C1>::value == MAP
  && is_container<C2>::value == MAP)), bool>::type
MergeAssociative(C1* c1, const C2& c2) {
  return true;
}