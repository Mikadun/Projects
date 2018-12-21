// Copyright 2018 Gribak Jaroslav

#include <functional>

struct NoTriviallyConstructible {
  NoTriviallyConstructible() = delete;
};

struct NoCopyConstructible {
  NoCopyConstructible(const NoCopyConstructible&) = delete;
  NoCopyConstructible(NoCopyConstructible&&) = delete;
};

template<>
struct Convert<NoCopyConstructible, NoTriviallyConstructible> {
  int operator()(const NoCopyConstructible&) { return 1; }
};

template<>
struct Convert<NoTriviallyConstructible, int> {
  int operator()(const NoCopyConstructible&) { return 1; }
};

template<class A, class B>
struct is_customly_convertible {
  static std::false_type Check(...);

  template<typename C, class = decltype(&C::operator())>
  static std::true_type Check(const C*);

  using type = decltype(Check(static_cast<Convert<A, B>*>(nullptr)));

  constexpr static bool value = type();
};
