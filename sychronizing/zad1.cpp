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
    std::mutex average_mtx;
    std::condition_variable condition;    
    bool terminate_pool = false;

public:
    TaskManager(unsigned int threadsNumber) {
        for (unsigned int i = 0; i < threadsNumber; i++) {
            std::thread th(&TaskManager::task_checking, this);
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

    void task_checking() {
        std::function<double()> job;
        while (true)
        { 
            {
                std::unique_lock<std::mutex> lock(queue_mtx);

                condition.wait(lock, [this]() {
                    return !task_queue.empty() || terminate_pool;
                });

                if (terminate_pool && task_queue.empty())
                {
                    return;
                }

                job = task_queue.front();
                task_queue.pop();
                lock.unlock();
                double result = job();

                lock.lock();
                result_list.push_back(result);
                std::cout << std::this_thread::get_id() << " taking task: " << result_list.size() << "\n";
                // average();

            }
        }
    };

    double average() {

        double average = 0.0;
        std::unique_lock<std::mutex> lock(average_mtx);
        double amount = result_list.size();

        for(size_t i = 0; i < amount; i++)
        {
            average += result_list[i];
        }
        lock.unlock();

        double result = average / amount;
        std::cout << result << "\n";
        return result;
    }

    void stop() {
        std::unique_lock<std::mutex> lock(queue_mtx);
            terminate_pool = true;
        lock.unlock();

        condition.notify_all();

        for(unsigned int i = 0; i < thread_list.size(); i++)
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

    for (int i = 1; i <= 10; i++)
    {
        std::function<double()> func = std::bind(f, i*1.0);
        manager.add_task(func);
    }
    manager.stop();
    manager.average();

    return 0;
}