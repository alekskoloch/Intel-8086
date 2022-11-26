#pragma once

#include "../Headers/headers.h"
#include "../Registry.h"
#include "../GUI/GUI.h"
#include "State.h"

enum class Order {IDLE, MOV, XCHN, NOT, INC, DEC, AND, OR, XOR, ADD, SUB};

class SimulatorState : public State
{
private:
    sf::Sprite background;
    std::unique_ptr<sf::Texture> backgroundTexture;

    std::unique_ptr<GUI::Assistant> assistant;

    bool letOnClick(float second = 0.2f);
    float clickTime;

    void loadBackgroundTexture();
    void setBackgroundTexture();
    void initializationBackground();
    void initializationOrder();

    void initializationVariables();
    void initializationAssistant();
    void initializationRegistry();
    void initializationOperationButtonsLabels();
    void initializationButtons();

    std::vector<std::unique_ptr<Registry>> registry;
    std::vector<std::string> registryLabels;

    std::vector<std::string> operationButtonsLabels;
    std::vector<std::unique_ptr<GUI::Button>> buttons;
    std::vector<std::unique_ptr<GUI::Button>> buttonsDisplayMethod;

    Order order;
    bool isOrder;
    int first;
    int second;
    void updateOrder(const float & dt);

    void deactiveAllRegistry();
    bool isAnyRegistryActive();
    bool isAnyButtonUse();
    void setDisplayMethod(DisplayMethod display);

    //temp function TEST
    void clear();

public:
    SimulatorState(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states);
    


    void update(const float & dt);
    void render();
};

 