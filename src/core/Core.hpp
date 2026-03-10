#pragma once
#include <cmath>
#include <cstdint>
#include <random>

namespace core {

struct Vec2 {
    float x{0.0f};
    float y{0.0f};
    Vec2() = default;
    Vec2(float px, float py) : x(px), y(py) {}
    Vec2 operator+(const Vec2& r) const { return {x + r.x, y + r.y}; }
    Vec2 operator-(const Vec2& r) const { return {x - r.x, y - r.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    float length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalized() const {
        float l = length();
        return l <= 0.0001f ? Vec2{} : Vec2{x / l, y / l};
    }
    static float distance(const Vec2& a, const Vec2& b) { return (a - b).length(); }
};

struct Color {
    float r{1}, g{1}, b{1}, a{1};
};

namespace Math {
constexpr float PI = 3.1415926535f;
inline float toRadians(float d) { return d * PI / 180.0f; }
inline float clamp(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
}

class Random {
public:
    explicit Random(uint32_t seed = 42) : rng(seed) {}
    int nextInt(int lo, int hi) {
        std::uniform_int_distribution<int> d(lo, hi);
        return d(rng);
    }
    float nextFloat(float lo, float hi) {
        std::uniform_real_distribution<float> d(lo, hi);
        return d(rng);
    }
private:
    std::mt19937 rng;
};

}
