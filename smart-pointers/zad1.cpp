#include <vector>
#include <memory>
#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>

std::condition_variable cond;

class FuelTank {
    unsigned int fuelCapacity;
    std::mutex tank_mtx;

public:
    FuelTank(unsigned int amount) {
        this->fuelCapacity = amount;
    }

    unsigned int getFuel(unsigned int amount) {
        std::unique_lock lock(tank_mtx);
        if (fuelCapacity >= amount) {
            fuelCapacity -= amount;
            std::cout << std::this_thread::get_id() <<" Consuming fuel: " << amount << ", tank capacity: " << fuelCapacity << "\n";
            return amount;
        }
        else {
            return 0;
        }
    }
};

class Engine {
    std::vector<std::shared_ptr<FuelTank>> fuelTankList;
    std::thread worker;
    unsigned int fuelDemand;
    unsigned int consumingInterval;
    bool wereTanksAdded = false;

public:

    Engine(unsigned int demand, unsigned int interval)
        : fuelDemand(demand), consumingInterval(interval)
    {
        worker = std::thread(&Engine::threadLoop, this);
    }

    void addFuelTank(std::shared_ptr<FuelTank> &tank) {
        fuelTankList.emplace_back(tank);
        wereTanksAdded = true;
    }

    void threadLoop() {
        while(true) {
            if (fuelTankList.empty() && wereTanksAdded)
            {
                return;
            }

            getFuel();
            std::this_thread::sleep_for(std::chrono::seconds(consumingInterval));
        }
    }

    void getFuel() {
        std::vector<int> detachTankIds;
        for (size_t i = 0; i < fuelTankList.size(); i++)
        {
            unsigned int amount = fuelTankList.at(i)->getFuel(fuelDemand);

            if (amount == 0)
            {
                detachTankIds.push_back(i);
            }
            else {
                break;
            }
        }
        
        if (detachTankIds.size() != 0) {
            for (size_t i = 0; i < detachTankIds.size(); i++)
            {
                fuelTankList.erase(fuelTankList.begin() + detachTankIds[i]);
            }
            std::cout << "detaching tank, current tanks amount: " << fuelTankList.size() << "\n";
        }
    }

    std::thread& getThread() {
        return worker;
    }

};

int main() {
    Engine e1(5, 2);
    Engine e2(1, 1);
    Engine e3(2, 3);

    std::vector<std::shared_ptr<FuelTank>> fueltanks;

    for (int i = 0; i < 10; i++) {
        fueltanks.emplace_back(std::make_shared<FuelTank>(10));
    }

    for (int i = 0; i < 10; i++) {
        e1.addFuelTank(fueltanks[i]);
        e2.addFuelTank(fueltanks[i]);
        e3.addFuelTank(fueltanks[i]);

    }

    e1.getThread().join();
    e2.getThread().join();
    e3.getThread().join();

    for (size_t i = 0; i < fueltanks.size(); i++)
    {
        std::cout << "fuel tank " << i << " use count: "<< fueltanks[i].use_count() << "\n";
    }
}