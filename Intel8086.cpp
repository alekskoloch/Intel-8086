#include "Intel8086.h"

void Intel8086::initializationDeltaTime()
{
    this->deltaTime = 0.f;
}

void Intel8086::initializationGraphicsSettings()
{
    
}

void Intel8086::initializationWindow()
{
    this->window.create(sf::VideoMode(this->graphicsSettings.windowWidth, this->graphicsSettings.windowHeight), this->graphicsSettings.windowTitle, sf::Style::Close);
    this->window.setFramerateLimit(this->graphicsSettings.windowFrameRateLimit);

    this->closeWindow = false;
}

void Intel8086::initializationMainMenuState()
{
    states.push(std::make_shared<MainMenuState>(&window, &states));
    //states.push(std::make_shared<SimulatorState>(&window));
}

void Intel8086::updateDeltaTime()
{
    this->deltaTime = deltaTimeClock.restart().asSeconds();
}

void Intel8086::updateSFMLEvents()
{
    //while (this->states->top()->getWindow().pollEvent(this->SFMLEvent))
    while (this->states.top()->getWindow()->pollEvent(this->SFMLEvent))
        if (this->SFMLEvent.type == sf::Event::Closed)
        {
            // this->states.top()->endState();
            this->closeWindow = true;
        }

    if (this->states.empty())
        std::cout << "STATES_EMPTY" << "\n";
}

void Intel8086::update()
{
    this->updateDeltaTime();

    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        if (this->states.top()->getWindow()->hasFocus())
        {
            this->states.top()->update(this->deltaTime);

            if (this->states.top()->getQuit() || this->closeWindow)
            {
                this->states.pop();
            }
        }
    }
}

void Intel8086::render()
{
    this->window.clear();

    if(!this->states.empty())
        this->states.top()->render();

    this->window.display();
}

Intel8086::Intel8086()
{
    initializationDeltaTime();
    initializationGraphicsSettings();
    initializationWindow();
    initializationMainMenuState();
}

void Intel8086::run()
{
    while (!this->states.empty())
    {
        this->update();
        this->render();
    }
}