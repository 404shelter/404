#include "systems/Systems.hpp"
#include "world/World.hpp"

using namespace systems;

void SpawnSystem::update(float dt, core::Random& rnd, world::Map& map, std::vector<passenger::Passenger>& passengers, int& nextPassengerId) {
    acc += dt;
    if (acc < interval || map.stations.size() < 2) return;
    acc = 0.0f;
    int from = rnd.nextInt(0, static_cast<int>(map.stations.size()) - 1);
    int to = from;
    while (to == from) to = rnd.nextInt(0, static_cast<int>(map.stations.size()) - 1);
    passenger::Passenger p{nextPassengerId++, from, to, passenger::PassengerState::Waiting};
    passengers.push_back(p);
    map.stations[from].waitingPassengerIds.push_back(p.id);
}

void WeekSystem::update(float dt) {
    acc += dt;
    if (acc >= 20.0f) {
        acc = 0.0f;
        ++week;
    }
}

void AchievementSystem::onPassengerDelivered() {
    ++delivered;
    if (delivered >= 10) unlockedFirst10 = true;
}
