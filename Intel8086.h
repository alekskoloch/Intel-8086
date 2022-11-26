#pragma once

#include "Headers/headers.h"
#include "Graphics/GraphicsSettings.h"
#include "States/MainMenuState.h"
#include "States/SimulatorState.h"

class Intel8086
{
private:
    sf::RenderWindow window;
    GraphicsSettings graphicsSettings;

    std::stack<std::shared_ptr<State>> states;

    sf::Event SFMLEvent;

    sf::Clock deltaTimeClock;
    float deltaTime;

    bool closeWindow;

    void initializationDeltaTime();
    void initializationGraphicsSettings();
    void initializationWindow();
    void initializationMainMenuState();

    void updateSFMLEvents();
    void updateDeltaTime();

    void update();
    void render();

public:
    Intel8086();

    void run();
};
