#pragma once
#include <functional>
#include <string>
#include "core/Core.hpp"

struct GLFWwindow;

namespace engine {

struct Camera {
    core::Vec2 offset{0, 0};
    float zoom{1.0f};
    core::Vec2 worldToScreen(const core::Vec2& w) const;
    core::Vec2 screenToWorld(const core::Vec2& s) const;
};

class Input {
public:
    core::Vec2 mouseScreen;
    bool leftDown{false};
    bool rightDown{false};
    bool keyPause{false};
    bool keyReset{false};
    bool keySave{false};
    void update(GLFWwindow* window);
};

class Engine {
public:
    bool init(int w, int h, const std::string& title);
    void run(const std::function<void(float)>& onUpdate, const std::function<void()>& onRender);
    void shutdown();

    GLFWwindow* window() const { return m_window; }
    Input& input() { return m_input; }
    Camera& camera() { return m_camera; }
    float deltaTime() const { return m_dt; }

private:
    GLFWwindow* m_window{nullptr};
    Input m_input;
    Camera m_camera;
    float m_dt{0.016f};
    double m_lastTime{0.0};
};

}
