#include <vector>
#include <functional>
#include <thread>
#include <future>
#include <condition_variable>

class TaskManager {
    std::vector<std::function<double()>> taskList;
    std::vector<std::future>> futuresList;
    std::thread_pool

    TaskManager(int threadsNumber) {
        for (int i = 0; i < threadsNumber; i++) {
            threadList.push(std::future);
        }
    }

    void add_task(std::function<double()> task) {
        taskList.push(task);
    }

    double average() {

    }

    void stop() {

    }

    std::vector<std::function<double()>> getTasks() {
        return taskList;
    }
}