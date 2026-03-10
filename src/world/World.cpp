#include "world/World.hpp"

using namespace world;

bool Map::canPlaceStation(const core::Vec2& p, float minDist) const {
    for (const auto& s : stations) {
        if (core::Vec2::distance(s.pos, p) < minDist) return false;
    }
    return !isOnRiver(p);
}

bool Map::isOnRiver(const core::Vec2& p) const {
    for (const auto& r : rivers) {
        float minY = std::min(r.a.y, r.b.y) - r.width * 0.5f;
        float maxY = std::max(r.a.y, r.b.y) + r.width * 0.5f;
        if (p.y >= minY && p.y <= maxY) return true;
    }
    return false;
}

Map CityGenerator::generate(int stationCount, float worldW, float worldH) {
    Map m;
    m.rivers.push_back({{0.0f, worldH * 0.45f}, {worldW, worldH * 0.45f}, 80.0f});
    m.bridges.push_back({{worldW * 0.2f, worldH * 0.45f}, {worldW * 0.3f, worldH * 0.45f}, 100.0f});
    m.bridges.push_back({{worldW * 0.7f, worldH * 0.45f}, {worldW * 0.8f, worldH * 0.45f}, 100.0f});
    m.districts.push_back({0, 1.0f});
    for (int i = 0; i < stationCount; ++i) {
        for (int t = 0; t < 100; ++t) {
            core::Vec2 p{rnd.nextFloat(80, worldW - 80), rnd.nextFloat(120, worldH - 80)};
            if (m.canPlaceStation(p, 90.0f)) {
                m.stations.push_back({i, p, static_cast<StationType>(rnd.nextInt(0, 2)), {}});
                break;
            }
        }
    }
    return m;
}
