#include "engine/Engine.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

using namespace engine;

core::Vec2 Camera::worldToScreen(const core::Vec2& w) const {
    return {(w.x + offset.x) * zoom, (w.y + offset.y) * zoom};
}

core::Vec2 Camera::screenToWorld(const core::Vec2& s) const {
    return {s.x / zoom - offset.x, s.y / zoom - offset.y};
}

void Input::update(GLFWwindow* window) {
    double x = 0, y = 0;
    glfwGetCursorPos(window, &x, &y);
    mouseScreen = {static_cast<float>(x), static_cast<float>(y)};
    leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    rightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    keyPause = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    keyReset = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
    keySave = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
}

bool Engine::init(int w, int h, const std::string& title) {
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    m_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!m_window) return false;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    m_lastTime = glfwGetTime();
    return true;
}

void Engine::run(const std::function<void(float)>& onUpdate, const std::function<void()>& onRender) {
    while (!glfwWindowShouldClose(m_window)) {
        double now = glfwGetTime();
        m_dt = static_cast<float>(now - m_lastTime);
        m_lastTime = now;
        m_input.update(m_window);

        onUpdate(m_dt);
        glClearColor(0.95f, 0.95f, 0.97f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        onRender();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Engine::shutdown() {
    if (m_window) glfwDestroyWindow(m_window);
    glfwTerminate();
}
