#pragma once
#include <vector>
#include "core/Core.hpp"

namespace world { struct Station; }
namespace metro { struct Line; }

namespace passenger {

enum class PassengerState { Waiting, OnTrain, Arrived };

struct Passenger {
    int id{};
    int fromStation{};
    int targetStation{};
    PassengerState state{PassengerState::Waiting};
};

class PathFinder {
public:
    int findBestLine(int fromStation, int targetStation, const std::vector<metro::Line>& lines) const;
};

class PassengerAI {
public:
    bool shouldBoard(int stationId, int targetStation, int lineId, const std::vector<metro::Line>& lines) const;
    bool shouldAlight(int stationId, int targetStation) const;
};

}
