#pragma once

#include "../Headers/headers.h"

class State
{
private:
    sf::RenderWindow * window;

    std::stack<std::shared_ptr<State>> * states;

    bool quit;
public:
    void initializationVariables();

    State(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states);

    sf::RenderWindow * getWindow();
    std::stack<std::shared_ptr<State>> * getStates();

    bool getQuit();
    void endState();

    virtual void render() = 0;
    virtual void update(const float & dt) = 0;
};


    