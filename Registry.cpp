#include "Registry.h"

bool Registry::letOnClick()
{
    if (this->clickTime >= 1)
    {
        this->clickTime = 0;
        return true;
    }
    else
        return false;
}

void Registry::initializationFont()
{
    this->font.loadFromFile("GUI/Fonts/Play-Bold.ttf");
}

void Registry::initializationVariables()
{
    this->registryStatus = RegistryStatus::IDLE;
    this->displayMethod = DisplayMethod::HEX;
    this->isActive = false;
    this->clickTime = 0;
}

void Registry::initializationShape()
{
    this->shape.setSize(sf::Vector2f(200.f, 50.f));
    this->shape.setPosition(positionX, positionY);
    this->shape.setOutlineThickness(3.f);
    this->shape.setOutlineColor(sf::Color::Black);

    this->text.setString(this->dataAsHexString());
    this->text.setFont(this->font);
    this->text.setStyle(sf::Text::Bold);

    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(24);
    this->text.setPosition(this->shape.getPosition().x + this->text.getGlobalBounds().width / 2,  this->shape.getPosition().y + ((this->shape.getSize().y / 2) - 18.f));
    
    this->textLabel.setFillColor(sf::Color::Black);
    this->textLabel.setString(this->label);
    this->textLabel.setFont(this->font);
    this->textLabel.setStyle(sf::Text::Regular);
    this->textLabel.setCharacterSize(14);
    this->textLabel.setPosition(this->shape.getPosition().x + (this->shape.getSize().x - (this->textLabel.getGlobalBounds().width + 4.f)), this->shape.getPosition().y + 2.f);
}

void Registry::styleIdle()
{
    this->shape.setFillColor(this->color);
}

void Registry::styleHover()
{
    this->shape.setFillColor(sf::Color(180, 255, 180, 200));
}

void Registry::styleActive()
{
    this->shape.setFillColor(sf::Color(30, 255, 30, 230));
}

void Registry::styleError()
{
    this->shape.setFillColor(sf::Color(255, 100, 30, 230));
}

std::string Registry::dataAsBinString()
{
    std::string result = std::bitset<8>(this->data).to_string();

    return result;
}

std::string Registry::dataAsDecString()
{
    return std::to_string(this->data);
}

std::string Registry::dataAsHexString()
{
    std::string result = "";
    int intData = static_cast<int>(this->data);
   
    while (intData != 0)
    {
        int temp = 0;
        char ch;

        temp = intData % 16;
 
        if (temp < 10)
        {
            ch = temp + 48;
        }
        else
        {
            ch = temp + 55;
        }
         
        result += ch;
        intData = intData / 16;
    }
     
    int i = 0, j = result.size() - 1;
    while(i <= j)
    {
      auto temp = result[i];
      result[i] = result[j];
      result[j] = temp;
      i++;
      j--;
    }

    if (result == "")
        return "0";
    return result;
}

Registry::Registry(sf::RenderWindow * window, float posX, float posY, std::string label, unsigned char data)
{
    this->data = data;

    this->window = window;

    this->positionX = posX;
    this->positionY = posY;

    this->label = label;

    this->color = sf::Color(255, 255, 255, 200);

    initializationFont();
    initializationShape();
    initializationVariables();
}

unsigned char Registry::getData()
{
    return this->data;
}

void Registry::setData(unsigned char value)
{
    this->data = value;
    if (this->displayMethod == DisplayMethod::BIN)
        this->text.setString(this->dataAsBinString());
    else if (this->displayMethod == DisplayMethod::DEC)
        this->text.setString(this->dataAsDecString());
    else if (this->displayMethod == DisplayMethod::HEX)
        this->text.setString(this->dataAsHexString());
}

void Registry::setData(std::string value)
{
    unsigned int result; 
    std::stringstream ss;

    if (value == "")
        value = "0";

    ss << std::hex << value;
    ss >> result;

    this->data = static_cast<int>(result);
    if (this->displayMethod == DisplayMethod::BIN)
        this->text.setString(this->dataAsBinString());
    else if (this->displayMethod == DisplayMethod::DEC)
        this->text.setString(this->dataAsDecString());
    else if (this->displayMethod == DisplayMethod::HEX)
        this->text.setString(this->dataAsHexString());
}

void Registry::setDataDisplay(DisplayMethod display)
{
    this->displayMethod = display;
    if (display == DisplayMethod::BIN)
        this->text.setString(this->dataAsBinString());
    else if (display == DisplayMethod::DEC)
        this->text.setString(this->dataAsDecString());
    else if (display == DisplayMethod::HEX)
        this->text.setString(this->dataAsHexString());
}

void Registry::setColor(sf::Color color)
{
    this->color = color;
}

bool Registry::getActive()
{
    return this->isActive;
}

void Registry::deactive()
{
    this->isActive = false;
}

void Registry::update(const float & dt)
{
    if (this->shape.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
    {
        this->registryStatus = RegistryStatus::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isActive && this->letOnClick())
        {
            this->isActive = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isActive && this->letOnClick())
        {
            this->deactive();
        }
    }
    else
        this->registryStatus = RegistryStatus::IDLE;

    if (this->isActive)
    {
        registryStatus == RegistryStatus::ACTIVE;
        this->styleActive();
    }
    else
    {
        if (registryStatus == RegistryStatus::IDLE)
            styleIdle();
        else if (registryStatus == RegistryStatus::HOVER)
            styleHover();
        else if (registryStatus == RegistryStatus::ERROR)
            styleError();
    }


    if (this->clickTime < 1)
        this->clickTime += dt;
}

void Registry::render()
{
    this->window->draw(this->shape);
    this->window->draw(this->text);
    this->window->draw(this->textLabel);
}

