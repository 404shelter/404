#include "passenger/Passenger.hpp"
#include "metro/Metro.hpp"

using namespace passenger;

int PathFinder::findBestLine(int fromStation, int targetStation, const std::vector<metro::Line>& lines) const {
    for (const auto& l : lines) {
        bool hasFrom = false, hasTarget = false;
        for (int st : l.stationIds) {
            hasFrom = hasFrom || st == fromStation;
            hasTarget = hasTarget || st == targetStation;
        }
        if (hasFrom && hasTarget) return l.id;
    }
    return lines.empty() ? -1 : lines.front().id;
}

bool PassengerAI::shouldBoard(int stationId, int targetStation, int lineId, const std::vector<metro::Line>& lines) const {
    for (const auto& l : lines) {
        if (l.id != lineId) continue;
        bool hasStation = false, hasTarget = false;
        for (int st : l.stationIds) {
            hasStation = hasStation || st == stationId;
            hasTarget = hasTarget || st == targetStation;
        }
        return hasStation && hasTarget;
    }
    return false;
}

bool PassengerAI::shouldAlight(int stationId, int targetStation) const {
    return stationId == targetStation;
}
