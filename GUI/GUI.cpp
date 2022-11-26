#include "GUI.h"

// Button

void GUI::Button::initFont()
{
    this->font.loadFromFile("GUI/Fonts/Play-Bold.ttf");
}

void GUI::Button::initButtonShape()
{
    if (this->buttonStyle == ButtonStyle::TRANSPARENT)
    {        
        this->buttonShape.setSize(sf::Vector2f(400.f, 60.f));
        this->buttonShape.setFillColor(sf::Color::Transparent);
        this->buttonShape.setPosition(this->positionX, this->positionY);
        this->buttonShape.setOutlineThickness(4.f);
    }
    else if (this->buttonStyle == ButtonStyle::OPAQUE)
    {
        this->buttonShape.setSize(sf::Vector2f(200.f, 60.f));
        this->buttonShape.setFillColor(sf::Color(128,128,128,200));
        this->buttonShape.setPosition(this->positionX, this->positionY);
        this->buttonShape.setOutlineThickness(4.f);
    }
}

void GUI::Button::initButtonText()
{
    this->buttonText.setString(this->buttonString);
    this->buttonText.setFont(this->font);
    this->buttonText.setStyle(sf::Text::Bold);

    //this->buttonText.setColor(sf::Color::White);
    this->buttonText.setCharacterSize(32);
    this->buttonText.setPosition(this->buttonShape.getPosition().x + 10.f,  this->buttonShape.getPosition().y + ((this->buttonShape.getSize().y / 2) - 18.f));
}

void GUI::Button::styleIdleAvailable(const float & dt)
{
    if (this->buttonStyle == ButtonStyle::TRANSPARENT)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Transparent);
            
        this->buttonText.setFillColor(sf::Color::Red);
    }
    else if (this->buttonStyle == ButtonStyle::OPAQUE)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Transparent);
            
        this->buttonText.setFillColor(sf::Color::Black);
    }
}

void GUI::Button::styleIdleNotAvailable(const float & dt)
{
    if (this->buttonStyle == ButtonStyle::TRANSPARENT)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Transparent);
            
        this->buttonText.setFillColor(sf::Color::Red);
    }
    else if (this->buttonStyle == ButtonStyle::OPAQUE)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Transparent);
            
        this->buttonText.setFillColor(sf::Color(220, 220, 220, 100));
    }
}

void GUI::Button::styleHover(const float & dt)
{
    if (this->buttonStyle == ButtonStyle::TRANSPARENT)
    {
        if (this->animationTimer < 1)
            this->animationTimer += (this->animationTimer) + dt;

        if (this->animationTimer >= 1)
            this->animationTimer = 1;

        this->buttonShape.setOutlineColor(sf::Color(30,200,225,255 * animationTimer));

        this->buttonText.setFillColor(sf::Color(30,200,225,255));
    }
    else if (this->buttonStyle == ButtonStyle::OPAQUE)
    {
        if (this->animationTimer < 1)
            this->animationTimer += (this->animationTimer) + dt;

        if (this->animationTimer >= 1)
            this->animationTimer = 1;

        this->buttonShape.setOutlineColor(sf::Color(30,200,225,255 * animationTimer));

        this->buttonText.setFillColor(sf::Color(30,200,225,255));
    }
}

void GUI::Button::styleActive(const float & dt)
{
    if (this->buttonStyle == ButtonStyle::TRANSPARENT)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Green);

        this->buttonText.setFillColor(sf::Color::Green);       
    }
    else if (this->buttonStyle == ButtonStyle::OPAQUE)
    {
        this->animationTimer = 0;

        this->buttonShape.setOutlineColor(sf::Color::Green);

        this->buttonText.setFillColor(sf::Color::Green); 
    }
}

void GUI::Button::initVariables()
{
    initFont();
    initButtonShape();
    initButtonText();

    this->animationTimer = 0;

    this->buttonState = ButtonState::IDLE;
}

GUI::Button::Button(sf::RenderWindow * window, ButtonStyle buttonStyle, float posX, float posY, std::string buttonString)
{
    this->window = window;
    this->buttonStyle = buttonStyle;

    this->positionX = posX;
    this->positionY = posY;

    this->availability = true;
    this->inUse = false;

    this->buttonString = buttonString;

    initVariables();
}

bool GUI::Button::getActive()
{
    return this->buttonState == ButtonState::ACTIVE;
}

bool GUI::Button::getAvailability()
{
    return this->availability;
}

void GUI::Button::setAvailability(bool availability)
{
    this->availability = availability;
}

void GUI::Button::use(bool inUse)
{
    this->inUse = inUse;
}

bool GUI::Button::getUse()
{
    return this->inUse;
}

void GUI::Button::update(const float & dt)
{
    if (this->buttonShape.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y) && this->availability)
    {
        this->buttonState = ButtonState::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->buttonState = ButtonState::ACTIVE;
    }
    else
    {
        this->buttonState = ButtonState::IDLE;
    }

    if (this->buttonShape.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            this->buttonState = ButtonState::IDLE;
            this->availability = true;
            this->inUse = false;
        }

    if (!this->inUse)
    {
        if (buttonState == ButtonState::IDLE)
        {
            if (this->availability)
                this->styleIdleAvailable(dt);
            else
                this->styleIdleNotAvailable(dt);
        }
        else if (buttonState == ButtonState::HOVER)
            this->styleHover(dt);
        else if (buttonState == ButtonState::ACTIVE)
            this->styleActive(dt);
    }
    else
    {
        this->styleActive(dt);
    }
}

void GUI::Button::render()
{
    this->window->draw(buttonShape);
    this->window->draw(buttonText);
}

// Assistant

void GUI::Assistant::initializationFont()
{
    this->font.loadFromFile("GUI/Fonts/Play-Bold.ttf");
}

void GUI::Assistant::initializationAssistantShape()
{
    this->assistantShape.setPosition(0.f, 1200.f);
    this->assistantShape.setSize(sf::Vector2f(1400.f, 200.f));
    this->assistantShape.setFillColor(sf::Color(10,10,15,220));
    this->assistantShape.setOutlineThickness(4.f);
    this->assistantShape.setOutlineColor(sf::Color(30,200,225,255));
}

void GUI::Assistant::initializationAssistantText()
{
    this->initializationFont();
    this->assistantText.setFont(this->font);
    this->assistantText.setString("NOT INITIALIZED");
    this->assistantText.setPosition(100.f, 1275.f);
    this->assistantText.setFillColor(sf::Color(30,200,225,255));
}

void GUI::Assistant::initializationVariables()
{
    this->initializationAssistantShape();
    this->initializationAssistantText();
}

GUI::Assistant::Assistant(sf::RenderWindow * window)
{
    this->window = window;

    this->initializationVariables();
}

void GUI::Assistant::setText(std::string text)
{
    this->assistantText.setString(text);
}

void GUI::Assistant::update(const float & dt)
{

}

void GUI::Assistant::render()
{
    this->window->draw(this->assistantShape);
    this->window->draw(this->assistantText);
}