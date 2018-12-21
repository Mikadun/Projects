// Copyright 2018 Gribak Jaroslav

#include <vector>

using std::vector;

template<typename T, int Dim>
struct GetType {
  using type = vector< typename GetType<T, Dim - 1>::type >;
};

template<typename T>
struct GetType<T, 0> {
  using type = T;
};

template<typename T>
auto initialize_vector(T val) -> typename GetType<T, 0>::type { return val; }

template<typename T, class D, class... Dim>
auto initialize_vector(T val, D d, Dim... dim)
-> typename GetType<T, sizeof...(Dim) + 1>::type {
  typename GetType<T, sizeof...(Dim) + 1>::type res;

  for (int i = 0; i < d; i++) {
    res.push_back(initialize_vector(val, dim...));
  }
  return res;
}
