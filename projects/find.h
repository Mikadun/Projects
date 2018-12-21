// Copyright 2018 Gribak Jaroslav

#include <type_traits>
#include <algorithm>
#include <iterator>

using std::iterator_traits;

template <class T, typename Iterator>
Iterator Find(const T& value, Iterator first, Iterator last) {
  using category = typename iterator_traits<Iterator>::iterator_category;
  if (std::is_same<category, std::random_access_iterator_tag>::value) {
    Iterator it = std::lower_bound(first, last, value);
    return (it != last && *it == value) ? it : last;
  } else {
    return std::find(first, last, value);
  }
}
