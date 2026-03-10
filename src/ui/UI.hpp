#pragma once
#include <string>
#include <vector>
#include "core/Core.hpp"

namespace ui {

struct Button {
    std::string text;
    core::Vec2 pos;
    core::Vec2 size;
    bool hovered{false};
    bool contains(const core::Vec2& p) const;
};

class HUD {
public:
    void draw(int week, int money, int delivered) const;
};

class Menu {
public:
    std::vector<Button> buttons;
    Menu();
    int click(const core::Vec2& worldPos) const;
};

class GameOverScreen {
public:
    bool visible{false};
    void draw() const;
};

}
