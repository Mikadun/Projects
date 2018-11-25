// Copyright 2018 Gribak Jaroslav

#include <inttypes.h>
#include <cstring>
#include <algorithm>

using std::memcpy;

class BufferedReader {
 public:
    explicit BufferedReader(PackageStream* stream);
    int32_t Read(char* buf, int32_t bytes);
 private:
    int32_t Left() { return size - idx; }
    PackageStream* stream;
    char* left;
    int32_t size;
    int32_t idx;
};

BufferedReader::BufferedReader(PackageStream* stream) {
  this->stream = stream;
  size = stream->PackageLen();
  idx = size;
}

int32_t BufferedReader::Read(char* buf, int32_t bytes) {
  int32_t i = 0;
  int32_t total_bytes = 0;
  int32_t bytes_to_copy = 0;
  if (Left() > 0) {
    bytes_to_copy = min(Left(), bytes);
    memcpy(buf, left + idx, bytes_to_copy);
    i += bytes_to_copy;
    idx += bytes_to_copy;
    total_bytes += bytes_to_copy;
  }
  if (total_bytes < bytes) {
    left = new char[size];
    while (bytes - total_bytes > 0) {
      int32_t read = stream->ReadPackage(left);
      bytes_to_copy = min(read, bytes - total_bytes);
      total_bytes += bytes_to_copy;
      memcpy(buf + i, left, bytes_to_copy);
      i += bytes_to_copy;
      idx = bytes_to_copy;
      if (read < size)
        break;
    }
  }
  return total_bytes;
}
