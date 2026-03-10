#pragma once
#include <vector>
#include "core/Core.hpp"
#include "engine/Engine.hpp"
#include "world/World.hpp"
#include "metro/Metro.hpp"
#include "passenger/Passenger.hpp"
#include "systems/Systems.hpp"
#include "ui/UI.hpp"
#include "render/Render.hpp"
#include "save/Save.hpp"

namespace game {

class Game {
public:
    bool init();
    void run();

    void update(float dt);
    void render();

    // save/load helpers
    world::Map& map() { return cityMap; }
    const world::Map& map() const { return cityMap; }
    std::vector<metro::Line>& linesRef() { return lines; }
    const std::vector<metro::Line>& linesRef() const { return lines; }
    std::vector<metro::Train>& trainsRef() { return trains; }
    const std::vector<metro::Train>& trainsRef() const { return trains; }
    std::vector<passenger::Passenger>& passengersRef() { return passengers; }
    const std::vector<passenger::Passenger>& passengersRef() const { return passengers; }
    systems::WeekSystem& weekRef() { return weekSystem; }
    const systems::WeekSystem& weekRef() const { return weekSystem; }
    systems::EconomySystem& economyRef() { return economySystem; }
    const systems::EconomySystem& economyRef() const { return economySystem; }

    int deliveredCount() const { return achievementSystem.delivered; }

private:
    engine::Engine eng;
    core::Random rnd{1234};

    world::Map cityMap;
    std::vector<metro::Line> lines;
    std::vector<metro::Train> trains;
    std::vector<passenger::Passenger> passengers;

    metro::Depot depot;
    metro::Scheduler scheduler;
    passenger::PassengerAI passengerAI;
    passenger::PathFinder pathFinder;

    systems::SpawnSystem spawnSystem;
    systems::WeekSystem weekSystem;
    systems::EconomySystem economySystem;
    systems::AchievementSystem achievementSystem;

    ui::HUD hud;
    ui::Menu menu;
    ui::GameOverScreen gameOver;
    render::Renderer renderer;
    save::SaveManager saveManager;

    int nextPassengerId{1};
    bool paused{false};

    void handleInput();
    passenger::Passenger* findPassenger(int id);
};

}
