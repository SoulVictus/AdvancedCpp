#include <vector>
#include <functional>
#include <thread>
#include <future>
#include <queue>
#include <condition_variable>
#include <iostream>

class TaskManager {

private:
    std::queue<std::function<double()>> task_queue;
    std::vector<double> result_list;
    std::vector<std::thread> thread_list;
    std::mutex queue_mtx;
    std::mutex threadpool_mtx;
    std::mutex average_mtx;
    std::condition_variable condition;    
    bool terminate_pool = false;
    bool is_counting_average = false;

public:
    TaskManager(unsigned int threadsNumber) {
        for (int i = 0; i < threadsNumber; i++) {
            std::thread th(task_checking);
            thread_list.push_back(std::move(th));
        }
    }

    void add_task(std::function<double()> task) {
        {
            std::unique_lock<std::mutex> lock(queue_mtx);
            task_queue.push(task);
        }

        condition.notify_one();
    }

    std::function<void()> task_checking = [&]() {
        std::function<double()> job;
        while (true)
        { 
            {
                std::unique_lock<std::mutex> lock(queue_mtx);

                condition.wait(lock, [&]() {
                    return !task_queue.empty() || terminate_pool;
                });

                if (terminate_pool && task_queue.empty())
                {
                    return;
                }

                job = task_queue.front();
                task_queue.pop();
                result_list.push_back(job());
                std::cout << "Taking task: " << result_list.size() << "\n";
                average();

            }
        }
    };

    void average() {
        // {
        //     std::unique_lock<std::mutex> lock(queue_mtx);
            double average = 0.0;

            for(size_t i = 0; i < result_list.size(); i++)
            {
                average += result_list[i];
            }

            std::cout << average / result_list.size() << "\n";
        // }
    }

    void stop() {
        std::unique_lock<std::mutex> lock(queue_mtx);
        terminate_pool = true;
        lock.unlock();

        condition.notify_all();

        for(int i = 0; i < thread_list.size(); i++)
        {
            thread_list.at(i).join();
        }
    }

    std::queue<std::function<double()>> getTasks() {
        return task_queue;
    }

};

double f(double number)
{
    return number;
}

int main()
{
    TaskManager manager(std::thread::hardware_concurrency());

    for (int i = 1; i < 50; i++)
    {
        std::function<double()> func = std::bind(f, i*1.0);
        manager.add_task(func);
    }
    manager.average();
    manager.stop();
    return 0;
}