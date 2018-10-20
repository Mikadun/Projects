// Copyright 2018 Gribak Jaroslav

#include <climits>
#include <cmath>

class PrimeNumberGenerator {
 public:
    explicit PrimeNumberGenerator(int start);
    int GetNextPrime();
 private:
    int state;
};

PrimeNumberGenerator::PrimeNumberGenerator(int start) {
  state = start - 1;
  if (state < 1)
    state = 1;
}

int PrimeNumberGenerator::GetNextPrime() {
  if (state >= INT_MAX)
    return -1;

  for (int i = state + 1; i < INT_MAX; i++) {
    bool is_prime = true;
    for (int j = 2; j <= sqrt(i); j++) {
      if (i % j == 0) {
        is_prime = false;
        break;
      }
    }

    if (is_prime) {
      state = i;
      return state;
    }
  }
  return -1;
}
