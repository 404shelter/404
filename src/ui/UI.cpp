#include "ui/UI.hpp"
#include <GL/gl.h>

using namespace ui;

bool Button::contains(const core::Vec2& p) const {
    return p.x >= pos.x && p.x <= pos.x + size.x && p.y >= pos.y && p.y <= pos.y + size.y;
}

void HUD::draw(int week, int money, int delivered) const {
    float w = 320.0f + week * 0.1f;
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(10, 10); glVertex2f(w, 10); glVertex2f(w, 60); glVertex2f(10, 60);
    glEnd();

    float incomeBar = static_cast<float>((money % 200)) / 200.0f;
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(20, 40); glVertex2f(20 + 200 * incomeBar, 40); glVertex2f(20 + 200 * incomeBar, 50); glVertex2f(20, 50);
    glEnd();

    float progress = static_cast<float>((delivered % 10)) / 10.0f;
    glColor3f(0.2f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(20, 22); glVertex2f(20 + 200 * progress, 22); glVertex2f(20 + 200 * progress, 32); glVertex2f(20, 32);
    glEnd();
}

Menu::Menu() {
    buttons.push_back({"Pause", {20, 80}, {90, 30}, false});
    buttons.push_back({"Save", {120, 80}, {90, 30}, false});
    buttons.push_back({"Reset", {220, 80}, {90, 30}, false});
}

int Menu::click(const core::Vec2& worldPos) const {
    for (int i = 0; i < static_cast<int>(buttons.size()); ++i) {
        if (buttons[i].contains(worldPos)) return i;
    }
    return -1;
}

void GameOverScreen::draw() const {
    if (!visible) return;
    glColor4f(0, 0, 0, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(200, 120); glVertex2f(1000, 120); glVertex2f(1000, 620); glVertex2f(200, 620);
    glEnd();
}
