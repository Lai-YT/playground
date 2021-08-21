#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>


void WorkerThread(std::string& data, bool& ready, bool& processed,
                  std::mutex& mutex, std::condition_variable& cond_var) {
  /* waits until main sends data */
  std::unique_lock<std::mutex> lock(mutex);
  std::cout << "WorkerThread waiting..." << '\n';
  cond_var.wait(lock, [&ready]() -> bool {
    return ready;
  });

  /* after the wait, we own the lock */
  std::cout << "WorkerThread is processing the data." << '\n';
  data += " after processing";

  /* send data back to main */
  processed = true;
  std::cout << "WorkerThread signals data processing completed." << '\n';

  /*
   * Optimization:
   * manual unlocking before notification allows the notified thread to wake up
   * immediately, otherwise it has to wait until unlocked in the destruction of unique_lock.
   */
   lock.unlock();
   cond_var.notify_one();
}


int main(int argc, char const *argv[]) {
  /* locks and resources */
  std::mutex mutex;
  std::condition_variable cond_var;
  std::string data = "";
  bool ready = false;
  bool processed = false;

  using std::ref;
  std::thread worker(WorkerThread, ref(data), ref(ready), ref(processed), ref(mutex), ref(cond_var));

  /* make sure the wait() statement inside WorkerThread is reached */
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  data = "Example data";
  /* send the data to the WorkerThread */
  std::unique_lock<std::mutex> lock(mutex);
  ready = true;
  std::cout << "main signals data ready for processing." << '\n';
  lock.unlock();
  cond_var.notify_one();

  /* wait for the worker */
  cond_var.wait(lock, [&processed]() {
    return processed;
  });
  worker.join();

  std::cout << "Back in main, data = " << data << '\n';


  return 0;
}
