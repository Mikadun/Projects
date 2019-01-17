#include <string>
#include <thread>
#include <mutex>
#include <utility>
#include <vector>

using std::thread;

std::pair<size_t, size_t> GetBorders(size_t i, size_t n, size_t len) {
  size_t r = (i+1)*n;
  if (r + n > len) 
    r = len;
  return std::make_pair(i*n, r);
}

void CaesarEncryptPart(std::string* s, size_t l, size_t r) {
  for (size_t i = l; i < r; i++) {
    (*s)[i] = 'a' + ((*s)[i] + 3 - 'a') % 26;
  }
}

void CaesarEncrypt(std::string* s) {
  size_t n = std::thread::hardware_concurrency();
  size_t cycles = std::min(s->length(), static_cast<size_t>(n));

  std::vector<thread> threads;

  size_t size = s->length() / n;

  for (size_t i = 0; i < cycles; i++) {
    std::pair<size_t, size_t> idx = GetBorders(i, size, s->length());
    threads.emplace_back(thread(CaesarEncryptPart, s, idx.first, idx.second));
  }

  for (thread& t : threads) {
    t.join();
  }
}
