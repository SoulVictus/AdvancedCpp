#include <iostream>
#include <vector>
#include <future>
#include <thread>

const int THREAD_NUM = 10;

void scalar_product(std::vector<double> v1, std::vector<double> v2, std::promise<double>&& promise)
{
    if (v1.size() != v2.size())
    {
        throw "vectors have different sizes";
    }
    else if (v1.size() == 0 || v2.size() == 0)
    {
        throw "one of vectors has size equal 0";
    }
    else {
        double sum = 0;

        for(int i = 0; i < v1.size(); i++)
        {
            sum += v1[i] * v2[i];
        }

        promise.set_value(sum);
    }
}

void test(std::vector<double> v1)
{
    std::cout << v1[0] << "\n";
}

int main()
{
    std::vector<double> v1{1.2, 3.4, 6.8};
    std::vector<double> v2{5.7, 7.2, 2.3};
    std::vector<std::thread> threads;

    double sum;

    for(int i = 0; i < THREAD_NUM; i++)
    {
        std::promise<double> promise;
        std::future<double> result = promise.get_future();
        threads.push_back(std::thread(scalar_product, v1, v2, std::move(promise)));
        sum += result.get();
    }
    
    for(int i = 0; i <threads.size(); i++)
    {
        threads[i].join();
    }

    std::cout << "result = " << sum << "\n";


}