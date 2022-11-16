#pragma once

#include "Headers/headers.h"
#include "Graphics/GraphicsSettings.h"

class Intel8086
{
private:
    sf::RenderWindow * window;
    GraphicsSettings * graphicsSettings;

    sf::Event SFMLEvent;

    void initializationGraphicsSettings();
    void initializationWindow();

    void updateSFMLEvents();

    void update();
    void render();

public:
    Intel8086();
    ~Intel8086();

    void run();
};
