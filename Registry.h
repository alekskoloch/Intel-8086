#pragma once

#include "Headers/headers.h"

enum class RegistryStatus {IDLE, HOVER, ACTIVE, ERROR};
enum class DisplayMethod {BIN, DEC, HEX};

class Registry
{
private:
    sf::RenderWindow * window;

    unsigned char data;
    std::string label;

    bool letOnClick();
    float clickTime;

    float positionX;
    float positionY;

    RegistryStatus registryStatus;
    DisplayMethod displayMethod;

    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
    sf::Text textLabel;

    sf::Color color;

    void initializationFont();
    void initializationShape();
    void initializationVariables();

    bool isActive;

    void styleIdle();
    void styleHover();
    void styleActive();
    void styleError();

    std::string dataAsBinString();
    std::string dataAsDecString();
    std::string dataAsHexString();

public:
    Registry(sf::RenderWindow * window, float posX, float posY, std::string label, unsigned char data);

    unsigned char getData();
    void setData(unsigned char value);
    void setData(std::string value);
    void setDataDisplay(DisplayMethod display);

    void setColor(sf::Color color);

    bool getActive();
    void deactive();

    void update(const float & dt);
    void render();
};
