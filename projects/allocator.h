// Copyright 2018 Gribak Jaroslav

#include <stdlib.h>
#include <cstddef>
#include <vector>

using std::vector;

struct Chunk {
    bool busy;
    char* buff;
};

class FixedAllocator {
 public:
    FixedAllocator(size_t chunk_size, size_t page_size);
    void* Allocate();
    void Deallocate(void* value);
    ~FixedAllocator();
 private:
    void AddPage();
    vector<Chunk*> buffer;
    size_t pages_count;
    size_t page_size;
    size_t chunk_size;
};

void FixedAllocator::AddPage() {
  Chunk* temp = new Chunk[page_size];
  for (size_t i = 0; i < page_size; i++) {
    temp[i].busy = false;
    temp[i].buff = new char[chunk_size];
  }
  buffer.push_back(temp);
}

FixedAllocator::FixedAllocator(size_t chunk_size, size_t page_size) {
  this->page_size = page_size;
  this->chunk_size = chunk_size;
  AddPage();
}

void* FixedAllocator::Allocate() {
  for (size_t i = 0; i < buffer.size(); i++) {
    for (size_t j = 0; j < page_size; j++) {
      if (!buffer[i][j].busy) {
        buffer[i][j].busy = true;
        return buffer[i][j].buff;
      }
    }
  }

  AddPage();
  return Allocate();
}

void FixedAllocator::Deallocate(void* value) {
  auto fixed_val = reinterpret_cast<char*>(value);

  for (size_t i = 0; i < buffer.size(); i++) {
    for (size_t j = 0; j < page_size; j++) {
      if (buffer[i][j].buff == fixed_val) {
        buffer[i][j].busy = false;
        return;
      }
    }
  }
}

FixedAllocator::~FixedAllocator() {
  for (size_t i = 0; i < buffer.size(); i++) {
    for (size_t j = 0; j < page_size; j++) {
      delete[] buffer[i][j].buff;
    }
    delete[] buffer[i];
  }
}
