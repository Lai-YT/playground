#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>


void WorkerThread(std::mutex& mutex, std::condition_variable& cond_var) {
  std::unique_lock<std::mutex> lock(mutex);
  std::cout << "WorkerThread waiting..." << '\n';
  cond_var.wait(lock);

  /* after the wait, we own the lock */
  std::cout << "WorkerThread is processing the data." << '\n';
}


int main(int argc, char const *argv[]) {
  std::mutex mutex;
  std::condition_variable cond_var;
  std::thread worker(WorkerThread, std::ref(mutex), std::ref(cond_var));

  /* make sure the wait() statement inside WorkerThread is reached */
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  std::cout << "main notifies one." << '\n';
  cond_var.notify_one();

  worker.join();
  std::cout << "main ended." << '\n';

  return 0;
}
