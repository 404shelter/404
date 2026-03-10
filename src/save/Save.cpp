#include "save/Save.hpp"
#include "Game.hpp"
#include <fstream>
#include <sstream>

using namespace save;

bool SaveManager::saveGame(const game::Game& game, const std::string& path) const {
    std::ofstream out(path);
    if (!out) return false;
    out << "WEEK " << game.weekRef().week << "\n";
    out << "MONEY " << game.economyRef().money << "\n";
    out << "PASSENGERS " << game.passengersRef().size() << "\n";
    for (const auto& p : game.passengersRef()) {
        out << p.id << " " << p.fromStation << " " << p.targetStation << " " << static_cast<int>(p.state) << "\n";
    }
    return true;
}

bool SaveManager::loadGame(game::Game& game, const std::string& path) const {
    std::ifstream in(path);
    if (!in) return false;
    std::string tag;
    int n = 0;
    while (in >> tag) {
        if (tag == "WEEK") {
            in >> game.weekRef().week;
        } else if (tag == "MONEY") {
            in >> game.economyRef().money;
        } else if (tag == "PASSENGERS") {
            in >> n;
            game.passengersRef().clear();
            for (int i = 0; i < n; ++i) {
                passenger::Passenger p;
                int st = 0;
                in >> p.id >> p.fromStation >> p.targetStation >> st;
                p.state = static_cast<passenger::PassengerState>(st);
                game.passengersRef().push_back(p);
            }
        }
    }
    return true;
}
