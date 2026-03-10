#pragma once

namespace game { class Game; }

namespace render {

class Renderer {
public:
    void drawFrame(const game::Game& game) const;
};

}
