#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <type_traits>

template <typename T>
class Queue {
 public:
    size_t Size() {
      std::unique_lock<std::mutex> mlock(mutex_);
      size_t size = queue_.size();
      mlock.unlock();
      return size;
    }

    T& Pop() {
      std::unique_lock<std::mutex> mlock(mutex_);
      while (!queue_.size()) {
          cond_.wait(mlock);
      }
      T& item = queue_.front();
      queue_.pop();
      return std::move(item);
    }

    void Push(T&& item) {
      std::unique_lock<std::mutex> mlock(mutex_);
      queue_.push(item);
      mlock.unlock();
      cond_.notify_one();
    }

    template<class... Args >
    void Emplace(Args&&... args) {
      std::unique_lock<std::mutex> mlock(mutex_);
      queue_.emplace(std::forward<Args>(args)...);
      mlock.unlock();
      cond_.notify_one();
    }

 private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};
