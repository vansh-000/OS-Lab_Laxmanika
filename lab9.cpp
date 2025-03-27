#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
class BinarySemaphore
{
private:
    bool available;
    std::mutex mtx;
    std::condition_variable cv;

public:
    BinarySemaphore() : available(true) {}
    void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]
                { return available; });
        available = false;
    }
    void signal()
    {
        std::unique_lock<std::mutex> lock(mtx);
        available = true;
        cv.notify_one();
    }
};
BinarySemaphore fileSemaphore;
void fileAccess(int id)
{
    std::cout << "Process " << id << " is waiting to access the file...\n";
    fileSemaphore.wait();
    std::cout << "Process " << id << " is accessing the file.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Process " << id << " has released the file.\n";
    fileSemaphore.signal();
}
int main()
{
    std::thread t1(fileAccess, 1);
    std::thread t2(fileAccess, 2);
    std::thread t3(fileAccess, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
