#pragma once

#include "../Headers/headers.h"

enum class ButtonStyle {TRANSPARENT, OPAQUE};

namespace GUI
{
    enum class ButtonState { IDLE, HOVER, ACTIVE };

    class Button
    {
    private:
        sf::RenderWindow * window;
        sf::Font font;

        ButtonStyle buttonStyle;

        ButtonState buttonState;

        sf::RectangleShape buttonShape;
        sf::Text buttonText;

        bool availability;
        bool inUse;

        float positionX;
        float positionY;

        float animationTimer;

        void initFont();
        void initButtonShape();
        void initButtonText(std::string string);

        void styleIdleAvailable(const float & dt);
        void styleIdleNotAvailable(const float & dt);
        void styleHover(const float & dt);
        void styleActive(const float & dt);

        void initVariables();
    public:
        Button(sf::RenderWindow * window, ButtonStyle buttonStyle, float posX, float posY, std::string buttonString);

        bool getActive();
        bool getAvailability();
        void setAvailability(bool availability);
        void setString(std::string string);
        std::string getString();
        void use(bool inUse);
        bool getUse();

        void update(const float & dt);
        void render();
    };
    
    class DropDownList
    {
    private:
        float clock;
        int state;

        sf::RenderWindow * window;
        std::unique_ptr<std::vector<Button>> dropDownList;
        std::vector<std::unique_ptr<Button>> listButtons;
        std::unique_ptr<Button> listButton; 

        bool active;

        void initializationVariables();
        void initializationClock();
        void initializationListButtons();
    public:
        DropDownList(sf::RenderWindow * window);

        int getState();

        void update(const float & dt);
        void render();
    };

    class Assistant
    {
    private:
        sf::RenderWindow * window;
        sf::Font font;

        sf::RectangleShape assistantShape;
        sf::Text assistantText;

        void initializationFont();
        void initializationAssistantShape();
        void initializationAssistantText();
        void initializationVariables();

    public:
        Assistant(sf::RenderWindow * window);

        void setText(std::string text);

        void update(const float & dt);
        void render();

    };
    
    class TextStream
    {
    private:
        sf::RenderWindow * window;
        std::string text;

        unsigned int maxChar;

        float clock;

        bool active;

        void initializationVariables();

    public:
        TextStream(sf::RenderWindow * window);

        std::string getText();
        void activeTextStream(unsigned int maxChar, bool b = true);

        void clear();

        void update(const float & dt);
        void render();
    };
}