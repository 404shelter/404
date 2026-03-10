#pragma once
#include <vector>
#include "core/Core.hpp"

namespace world {

enum class StationType { Circle, Triangle, Square };

struct River { core::Vec2 a, b; float width{60.0f}; };
struct Bridge { core::Vec2 a, b; float width{80.0f}; };
struct District { int id{}; float passengerRate{1.0f}; };

struct Station {
    int id{};
    core::Vec2 pos;
    StationType type{StationType::Circle};
    std::vector<int> waitingPassengerIds;
};

class Map {
public:
    std::vector<River> rivers;
    std::vector<Bridge> bridges;
    std::vector<District> districts;
    std::vector<Station> stations;

    bool canPlaceStation(const core::Vec2& p, float minDist) const;
    bool isOnRiver(const core::Vec2& p) const;
};

class CityGenerator {
public:
    explicit CityGenerator(core::Random& r) : rnd(r) {}
    Map generate(int stationCount, float worldW, float worldH);
private:
    core::Random& rnd;
};

}
