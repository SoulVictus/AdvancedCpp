#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <future>

std::mutex mutx;

static std::atomic<unsigned long long> thread_counter;

unsigned long long thread_id() {
    thread_local unsigned long long id = ++thread_counter;
    return id;
}

void f(std::string text)
{
    mutx.lock();
    std::cout << thread_id() << " " << text << "\n";
    mutx.unlock();
}

void async3(std::launch policy)
{
    auto as1 = std::async(policy ,&f, "test1");
    as1.get();
}

int main()
{
    std::thread th(f, "ala ma");
    std::thread th2(f, "kota ma");
    th.join();
    th2.join();

    async3(std::launch::async);
    return 0;
}