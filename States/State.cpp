#include "State.h"

void State::initializationVariables()
{
    this->quit = false;
}

State::State(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states)
{
    this->window = window;
    this->states = states;
    this->initializationVariables();
}

sf::RenderWindow * State::getWindow()
{
    return this->window;
}

std::stack<std::shared_ptr<State>> * State::getStates()
{
    return this->states;
}

bool State::getQuit()
{
    return quit;
}

void State::endState()
{
    this->quit = true;
}