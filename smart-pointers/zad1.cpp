#include <vector>
#include <memory>

class FuelTank {
    unsigned int fuelAmount;

    FuelTank(unsigned int amount) {
        this.fuelAmount = amount;
    }

    unsigned int getFuel(unsigned int amount) {
        if (fuelAmount > amount) {
            fuelAmount -= amount;
            return amount;
        }
        else {
            return 0;
        }
    }
}

class Engine {
    std::vector<std::shared_ptr<FuelTank>> fuelTankList;
    unsigned int fuelDemand;
    unsigned int consumingInterval;

    Engine(unsigned int demand, unsigned int interval)
        : fuelDemand(demand), consumingInterval(interval)
    {
    }

    void addFuelTank(FuelTank &tank) {
        fuelTankList.emplace_back(tank);l
    }
}

int main() {
    Engine e1(5, 2);
    Engine el2(1, 1);
    Engine el3(2, 3);

    std::vector<shared_ptr<FuelTank>> fueltanks;

    for (int i = 0; i < 10; i++) {
        fueltanks.emplace_back(new FuelTank(10));
    }

    for (int i = 0; i < 10; i++) {
        el1.addFuelTank(fueltanks[i]);
        el2.addFuelTank(fueltanks[i]);
        el3.addFuelTank(fueltanks[i]);

    }
}