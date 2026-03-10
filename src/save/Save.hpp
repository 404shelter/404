#pragma once
#include <string>

namespace game { class Game; }

namespace save {

class SaveManager {
public:
    bool saveGame(const game::Game& game, const std::string& path) const;
    bool loadGame(game::Game& game, const std::string& path) const;
};

}
