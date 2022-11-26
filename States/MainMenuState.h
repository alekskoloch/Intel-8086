#pragma once

#include "../Headers/headers.h"
#include "State.h"
#include "../GUI/GUI.h"

class MainMenuState : public State
{
private:
    sf::Sprite background;
    std::unique_ptr<sf::Texture> texture;

    sf::RectangleShape buttonsBackground;

    void loadBackgroundTexture();
    void setBackgroundTexture();

    void initializationButtonsBackground();
    void initializationBackground();

    float tempTestDeltaTime;

    std::unique_ptr<GUI::Button> startButton;
    std::unique_ptr<GUI::Button> quitButton;
public:
    MainMenuState(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states);

    void initializationVariables();

    void update(const float & dt);
    void render();
};

 