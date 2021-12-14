#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <future>

std::mutex mutx;

static std::atomic<unsigned long long> thread_counter = 0;

unsigned long long thread_id() {
    thread_local unsigned long long id = ++thread_counter;
    return id;
}

void f(std::string text)
{
    std::lock_guard<std::mutex> mtx_guard(mutx);
    std::cout << thread_id() << " " << thread_id() << " " << text << "\n";
}



void async3(std::launch policy)
{
    auto as1 = std::async(policy ,&f, "test3");
    as1.get();
}

void async2(std::launch policy)
{
    auto as1 = std::async(policy ,&f, "test2");
    async3(policy);
    as1.get();
}

void async(std::launch policy)
{
    auto as1 = std::async(policy ,&f, "test1");
    async2(policy);
    as1.get();
}

int main()
{
    std::thread th(&f, "ala ma");
    std::thread th2(&f, "kota ma");
    th.join();
    th2.join();

    async(std::launch::async);
    async(std::launch::deferred);
    return 0;
}