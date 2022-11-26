#include "MainMenuState.h"
#include "SimulatorState.h"
#include "../GUI/GUI.h"

void MainMenuState::loadBackgroundTexture()
{
    sf::Texture temp;
    temp.loadFromFile("Images/mainMenuBackground.jpg");
    this->texture = std::make_unique<sf::Texture>(std::move(temp));
}

void MainMenuState::setBackgroundTexture()
{
    background.setTexture(*this->texture);
}

void MainMenuState::initializationButtonsBackground()
{
    this->buttonsBackground.setSize(sf::Vector2f(this->getWindow()->getSize().x / 3, this->getWindow()->getSize().y));
    this->buttonsBackground.setPosition(70.f,0.f);
    this->buttonsBackground.setFillColor(sf::Color(0, 0, 0, 200));
}

void MainMenuState::initializationBackground()
{
    this->loadBackgroundTexture();
    this->setBackgroundTexture();
}

void MainMenuState::initializationVariables()
{
    this->initializationButtonsBackground();
    this->initializationBackground();

    this->startButton = std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::TRANSPARENT, 100.f, 100.f, "START");
    this->quitButton = std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::TRANSPARENT, 100.f, 180.f, "QUIT");
    
    //this->tempTestDeltaTime = 0;
}

MainMenuState::MainMenuState(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states) : State(window, states)
{
    this->initializationVariables();
}

void MainMenuState::update(const float & dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->getStates()->push(std::make_shared<SimulatorState>(this->getWindow(), this->getStates()));

    this->startButton->update(dt);
    this->quitButton->update(dt);

    if (this->startButton->getActive())
    {
        this->getStates()->push(std::make_shared<SimulatorState>(this->getWindow(), this->getStates()));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        this->endState();

    if (this->quitButton->getActive())
    {
        this->endState();
    }
}

void MainMenuState::render()
{   
    this->getWindow()->draw(background);
    this->getWindow()->draw(buttonsBackground);
    this->startButton->render();
    this->quitButton->render();
}
