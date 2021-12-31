/*
 * What this piece of code does:
 * The producer produces a product per second and put it in a queue.
 * The queue notifies the consumer when a new product is ready.
 * The consumer can take the product out and have some operations on it.
 */


#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>


class CondVarQueue {
public:
  void Push(const int i) {
    std::lock_guard<std::mutex> lock(mutex_);
    produced_nums_.push(i);
    can_notify_ = true;
    cond_var_.notify_one();
  }

  template<typename Consumer>
  void Consume(const Consumer& consumer) {
    std::unique_lock<std::mutex> lock(mutex_);
    while (!is_done_) {
      /*
       * Prediacte or loop to avoid spurious wakeups,
       * wakes up only when the can_notify_ is true.
       */
      cond_var_.wait(lock, [this]() -> bool {
        return can_notify_;
      });
      while (!produced_nums_.empty()) {
        consumer(produced_nums_.front());
        produced_nums_.pop();
      }
      can_notify_ = false;
    }
  }

  void Close() {
    std::lock_guard<std::mutex> lock(mutex_);
    is_done_ = true;
    can_notify_ = true;
    cond_var_.notify_one();
  }

private:
  std::queue<int> produced_nums_;
  std::mutex mutex_;
  std::condition_variable cond_var_;
  bool is_done_ = false;
  bool can_notify_ = false;
};


int main(int argc, char const *argv[]) {
  CondVarQueue queue;

  std::thread producer([&queue]() -> void {
    for (int i = 0; i < 5; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Producing " << i << ".\n";
      queue.Push(i);
    }
    queue.Close();
  });

  std::thread consumer([&queue]() -> void {
    queue.Consume([](const int input) -> void {
      std::cout << "Consuming " << input << ".\n";
    });
  });

  producer.join();
  consumer.join();
  /*
   * Producing 0.
   * Consuming 0.
   * Producing 1.
   * Consuming 1.
   * Producing 2.
   *
   * Consuming 2.
   * Producing 3.
   * Consuming 3.
   * Producing 4.
   * Consuming 4.
   */

  return 0;
}
