#include "render/Render.hpp"
#include "Game.hpp"
#include <cmath>
#include <GL/gl.h>

using namespace render;

static void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 24; ++i) {
        float a = i * 2.0f * 3.1415926f / 24.0f;
        glVertex2f(cx + std::cos(a) * r, cy + std::sin(a) * r);
    }
    glEnd();
}

void Renderer::drawFrame(const game::Game& game) const {
    const auto& map = game.map();
    for (const auto& river : map.rivers) {
        glColor3f(0.5f, 0.7f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(river.a.x, river.a.y - river.width * 0.5f);
        glVertex2f(river.b.x, river.b.y - river.width * 0.5f);
        glVertex2f(river.b.x, river.b.y + river.width * 0.5f);
        glVertex2f(river.a.x, river.a.y + river.width * 0.5f);
        glEnd();
    }

    for (const auto& line : game.linesRef()) {
        glColor3f(line.color.r, line.color.g, line.color.b);
        glLineWidth(4.0f);
        glBegin(GL_LINE_STRIP);
        for (int sid : line.stationIds) {
            const auto& p = map.stations[sid].pos;
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }

    for (const auto& s : map.stations) {
        glColor3f(0.18f, 0.18f, 0.2f);
        drawCircle(s.pos.x, s.pos.y, 14.0f);
    }

    for (const auto& t : game.trainsRef()) {
        glColor3f(0.95f, 0.25f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(t.position.x - 10, t.position.y - 6);
        glVertex2f(t.position.x + 10, t.position.y - 6);
        glVertex2f(t.position.x + 10, t.position.y + 6);
        glVertex2f(t.position.x - 10, t.position.y + 6);
        glEnd();
    }
}
