#pragma once

#include "../Headers/headers.h"
#include "../Registry.h"
#include "../GUI/GUI.h"
#include "../MemoryBus.h"
#include "State.h"

enum class Order {IDLE, MOV, XCHN, NOT, INC, DEC, AND, OR, XOR, ADD, SUB};

class SimulatorState : public State
{
private:
    sf::Sprite background;
    std::unique_ptr<sf::Texture> backgroundTexture;

    std::unique_ptr<GUI::DropDownList> displayMethodDropDownList;

    std::unique_ptr<GUI::Assistant> assistant;

    std::unique_ptr<GUI::TextStream> textStream;

    std::unique_ptr<MemoryBus> memoryBus;

    bool letOnClick(float second = 0.2f);
    bool addressEnter;
    float clickTime;

    void loadBackgroundTexture();
    void setBackgroundTexture();
    void initializationBackground();
    void initializationOrder();

    void initializationVariables();
    void initializationdisplayMethodDropDownList();
    void initializationAssistant();
    void initializationRegistry();
    void initializationOperationButtonsLabels();
    void initializationButtons();

    std::vector<std::unique_ptr<Registry>> registry;
    std::vector<std::string> registryLabels;

    std::vector<std::string> operationButtonsLabels;
    std::vector<std::unique_ptr<GUI::Button>> buttons;
    std::unique_ptr<GUI::Button> addressButton;

    Order order;
    bool isOrder;
    bool saveData;
    int first;
    int second;
    void updateOrder(const float & dt);

    void deactiveAllRegistry();
    bool isAnyRegistryActive();
    bool isAnyButtonUse();
    void setDisplayMethod(DisplayMethod display);

public:
    SimulatorState(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states);
    


    void update(const float & dt);
    void render();
};

 