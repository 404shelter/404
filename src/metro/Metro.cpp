#include "metro/Metro.hpp"
#include "world/World.hpp"

using namespace metro;

bool Line::containsStation(int sid) const {
    for (int id : stationIds) if (id == sid) return true;
    return false;
}

void Train::update(float dt, const Line& line, const world::Map& map) {
    if (line.stationIds.size() < 2) return;
    int fromIdx = currentSegment;
    int toIdx = forward ? currentSegment + 1 : currentSegment - 1;
    const auto& a = map.stations[line.stationIds[fromIdx]].pos;
    const auto& b = map.stations[line.stationIds[toIdx]].pos;
    float segLen = core::Vec2::distance(a, b);
    if (segLen < 1.0f) segLen = 1.0f;
    segmentT += (speed * dt) / segLen;
    if (segmentT >= 1.0f) {
        segmentT = 0.0f;
        currentSegment = toIdx;
    }
    position = a + (b - a) * segmentT;
}

void Scheduler::update(Train& train, const Line& line) {
    if (line.stationIds.size() < 2) return;
    if (train.forward && train.currentSegment >= static_cast<int>(line.stationIds.size()) - 1) {
        train.forward = false;
    } else if (!train.forward && train.currentSegment <= 0) {
        train.forward = true;
    }
}
