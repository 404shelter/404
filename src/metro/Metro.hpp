#pragma once
#include <vector>
#include "core/Core.hpp"

namespace world { class Map; }
namespace passenger { struct Passenger; class PassengerAI; }

namespace metro {

struct Line {
    int id{};
    std::vector<int> stationIds;
    core::Color color{1, 0.6f, 0.1f, 1};
    bool containsStation(int sid) const;
};

struct Train {
    int id{};
    int lineId{};
    int currentSegment{};
    bool forward{true};
    float segmentT{0.0f};
    float speed{120.0f};
    int maxPassengers{8};
    std::vector<int> onboardPassengerIds;
    core::Vec2 position;

    void update(float dt, const Line& line, const world::Map& map);
};

struct Depot {
    int locomotiveStock{3};
    int carriageStock{6};
};

class Scheduler {
public:
    void update(Train& train, const Line& line);
};

}
