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

void GUI::Button::initButtonText(std::string string)
{
    this->buttonText.setString(string);
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

    this->initVariables();
    this->initButtonText(buttonString);
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

void GUI::Button::setString(std::string string)
{
    this->buttonText.setString(string);
}

std::string GUI::Button::getString()
{
    return this->buttonText.getString();
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

// DorpDownList

void GUI::DropDownList::initializationClock()
{
    this->clock = 0.f;
}

void GUI::DropDownList::initializationListButtons()
{
    this->listButtons.push_back(std::make_unique<Button>(this->window, ButtonStyle::OPAQUE, 100.f, 1000.f, "BIN"));
    this->listButtons.push_back(std::make_unique<Button>(this->window, ButtonStyle::OPAQUE, 100.f, 930.f, "DEC"));
    this->listButtons.push_back(std::make_unique<Button>(this->window, ButtonStyle::OPAQUE, 100.f, 860.f, "HEX"));
}

void GUI::DropDownList::initializationVariables()
{
    this->listButton = std::make_unique<Button>(this->window, ButtonStyle::OPAQUE, 100.f, 1000.f, "DISPLAY");

    this->initializationListButtons();
    this->initializationClock();

    this->active = false;
}

GUI::DropDownList::DropDownList(sf::RenderWindow * window)
{
    this->window = window;

    this->state = 3;

    this->initializationVariables();
}

int GUI::DropDownList::getState()
{
    return this->state;
}

void GUI::DropDownList::update(const float & dt)
{
    if (!active)
        this->listButton->update(dt);

    if (this->listButton->getActive() && !this->active && this->clock >= 0.3)
    {
        this->clock = 0;
        this->active = true;
    }

    if (active)
        for (int i = 0; i < this->listButtons.size(); i++)
            this->listButtons[i]->update(dt);

    if (active)
        for (int i = 0; i < this->listButtons.size(); i++)
            if(this->listButtons[i]->getActive() && this->clock >= 0.3f)
            {
                this->state = 1 + i;
                this->clock = 0;
                this->active = false;
            }

    if (this->clock <= 1.f)
        this->clock += dt;
}

void GUI::DropDownList::render()
{
    if (!active)
        this->listButton->render();

    if (active)
        for (int i = 0; i < this->listButtons.size(); i++)
            this->listButtons[i]->render();
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
    this->assistantShape.setFillColor(sf::Color(10,10,15,255));
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

// TextStream
void GUI::TextStream::initializationVariables()
{
    this->text = "";
    this->active= false;

    this->maxChar = 0;

    this->clock = 0;
}

std::string GUI::TextStream::getText()
{
    return this->text;
}

void GUI::TextStream::activeTextStream(unsigned int maxChar, bool b)
{
    this->active = b;

    this->maxChar = maxChar;

    if (b == false)
        this->text = "";
}

void GUI::TextStream::clear()
{
    this->text = "";
    this->active = false;
}

GUI::TextStream::TextStream(sf::RenderWindow * window)
{
    this->window = window;

    this->initializationVariables();
}

void GUI::TextStream::update(const float & dt)
{
    if (clock <= 0.2f)
        clock += dt;

    if (this->active)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->active = false;

        if (this->text.size() < this->maxChar)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "0";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "1";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "2";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "3";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "4";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "5";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "6";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "7";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "8";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "9";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "A";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "B";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "C";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "D";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "E";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && this->clock >= 0.2f)
            {
                this->clock = 0.f;
                this->text += "F";
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) && this->clock >= 0.2f)
        {
            this->clock = 0.f;
            if (this->text.size() > 0)
                this->text = this->text.substr(0, this->text.size()-1);
        }
    }
}