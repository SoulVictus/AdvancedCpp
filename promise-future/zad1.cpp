#include <iostream>
#include <vector>
#include <future>
#include <thread>

const int THREAD_NUM = 10;

void scalar_product(std::vector<double> v1, std::vector<double> v2, std::promise<double>&& promise)
{
    try{
        if (v1.size() != v2.size())
        {
            throw std::runtime_error("vectors have different sizes");
        }
        else if (v1.size() == 0 || v2.size() == 0)
        {
            throw std::runtime_error("one of vectors has size equal 0");
        }
        else {
            double sum = 0;

            for(size_t i = 0; i < v1.size(); i++)
            {
                sum += v1[i] * v2[i];
            }

            promise.set_value(sum);
        }
    }
    catch (const std::exception& e)
    {
        promise.set_exception(std::current_exception());
    }
}

int main()
{
    std::vector<double> v1;
    std::vector<double> v2;
    std::vector<std::thread> threads;
    std::vector<std::future<double>> futures;

    double sum = 0.0f;

    for(int i = 0; i < 100000; i++)
    {
        v1.push_back(i+1.0);
        v2.push_back(i+1.0);
    }

    for(size_t i = 0; i < THREAD_NUM; i++)
    {
        std::promise<double> promise;
        futures.push_back(promise.get_future());
        threads.emplace_back(scalar_product, v1, v2, std::move(promise));
    }

    for(size_t i = 0; i < THREAD_NUM; i++)
    {
        try
        {
            sum += futures[i].get();
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception from the thread: " << e.what() << "\n";
        }
    }
    
    for(size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    std::cout << "result = " << sum << "\n";

    return 0;
}