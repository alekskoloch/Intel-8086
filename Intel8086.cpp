#include "Intel8086.h"

void Intel8086::initializationGraphicsSettings()
{
    this->graphicsSettings = new GraphicsSettings();
}

void Intel8086::initializationWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(this->graphicsSettings->windowWidth, this->graphicsSettings->windowHeight), this->graphicsSettings->windowTitle, sf::Style::Close);
    this->window->setFramerateLimit(this->graphicsSettings->windowFrameRateLimit);
}

void Intel8086::updateSFMLEvents()
{
    while (this->window->pollEvent(this->SFMLEvent))
        if (this->SFMLEvent.type == sf::Event::Closed)
            this->window->close();
}

void Intel8086::update()
{
    this->updateSFMLEvents();
}

void Intel8086::render()
{
    this->window->clear();

    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Blue);
    shape.setSize(sf::Vector2f(300.f, 300.f));
    shape.setPosition(100, 100);

    this->window->draw(shape);

    this->window->display();
}

Intel8086::Intel8086()
{
    initializationGraphicsSettings();
    initializationWindow();
}

Intel8086::~Intel8086()
{
    delete this->graphicsSettings;
    delete this->window;
}

void Intel8086::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}