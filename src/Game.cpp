#include "Game.hpp"
#include <algorithm>
#include <iostream>

using namespace game;

bool Game::init() {
    if (!eng.init(1280, 720, "Mini Metro Advanced Clone")) return false;
    world::CityGenerator gen(rnd);
    cityMap = gen.generate(12, 1280, 720);

    lines.push_back({0, {0, 1, 2, 3, 4}, {1, 0.4f, 0.1f, 1}});
    lines.push_back({1, {5, 6, 7, 8, 9, 10, 11}, {0.2f, 0.7f, 1.0f, 1}});

    trains.push_back({0, 0, 0, true, 0.0f, 130.0f, 8, {}, cityMap.stations[0].pos});
    trains.push_back({1, 1, 0, true, 0.0f, 120.0f, 8, {}, cityMap.stations[5].pos});
    return true;
}

void Game::run() {
    eng.run([this](float dt) { update(dt); }, [this]() { render(); });
    eng.shutdown();
}

passenger::Passenger* Game::findPassenger(int id) {
    for (auto& p : passengers) if (p.id == id) return &p;
    return nullptr;
}

void Game::handleInput() {
    auto& in = eng.input();
    if (in.keyPause) paused = !paused;
    if (in.keyReset) {
        passengers.clear();
        for (auto& s : cityMap.stations) s.waitingPassengerIds.clear();
        achievementSystem.delivered = 0;
    }
    if (in.keySave) {
        saveManager.saveGame(*this, "savegame.txt");
    }

    core::Vec2 worldMouse = in.mouseScreen;
    if (in.leftDown) {
        int action = menu.click(worldMouse);
        if (action == 0) paused = !paused;
        if (action == 1) saveManager.saveGame(*this, "savegame.txt");
        if (action == 2) {
            saveManager.loadGame(*this, "savegame.txt");
        }
    }
}

void Game::update(float dt) {
    handleInput();
    if (paused) return;

    spawnSystem.update(dt, rnd, cityMap, passengers, nextPassengerId);
    weekSystem.update(dt);

    for (size_t i = 0; i < trains.size(); ++i) {
        auto& t = trains[i];
        auto& line = lines[t.lineId];
        scheduler.update(t, line);
        t.update(dt, line, cityMap);

        for (int sid : line.stationIds) {
            if (core::Vec2::distance(cityMap.stations[sid].pos, t.position) < 8.0f) {
                auto& wait = cityMap.stations[sid].waitingPassengerIds;
                for (auto it = wait.begin(); it != wait.end() && (int)t.onboardPassengerIds.size() < t.maxPassengers;) {
                    passenger::Passenger* p = findPassenger(*it);
                    if (p && p->state == passenger::PassengerState::Waiting && passengerAI.shouldBoard(sid, p->targetStation, line.id, lines)) {
                        p->state = passenger::PassengerState::OnTrain;
                        t.onboardPassengerIds.push_back(p->id);
                        it = wait.erase(it);
                    } else {
                        ++it;
                    }
                }

                for (auto it = t.onboardPassengerIds.begin(); it != t.onboardPassengerIds.end();) {
                    passenger::Passenger* p = findPassenger(*it);
                    if (p && passengerAI.shouldAlight(sid, p->targetStation)) {
                        p->state = passenger::PassengerState::Arrived;
                        economySystem.earn(3);
                        achievementSystem.onPassengerDelivered();
                        it = t.onboardPassengerIds.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }
    }

    if (weekSystem.week > 12) gameOver.visible = true;
}

void Game::render() {
    renderer.drawFrame(*this);
    hud.draw(weekSystem.week, economySystem.money, achievementSystem.delivered);
    gameOver.draw();
}
