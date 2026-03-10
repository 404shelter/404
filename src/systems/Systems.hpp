#pragma once
#include <vector>
#include "core/Core.hpp"
#include "passenger/Passenger.hpp"

namespace world { class Map; }

namespace systems {

class SpawnSystem {
public:
    float interval{2.5f};
    float acc{0.0f};
    void update(float dt, core::Random& rnd, world::Map& map, std::vector<passenger::Passenger>& passengers, int& nextPassengerId);
};

class WeekSystem {
public:
    int week{1};
    float acc{0.0f};
    void update(float dt);
};

class EconomySystem {
public:
    int money{100};
    void earn(int amount) { money += amount; }
    bool spend(int amount) { if (money < amount) return false; money -= amount; return true; }
};

class AchievementSystem {
public:
    int delivered{0};
    bool unlockedFirst10{false};
    void onPassengerDelivered();
};

}
