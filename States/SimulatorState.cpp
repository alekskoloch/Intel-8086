#include "SimulatorState.h"

bool SimulatorState::letOnClick(float second)
{
    if (this->clickTime >= second)
    {
        this->clickTime = 0;
        return true;
    }
    else
        return false;
}

void SimulatorState::loadBackgroundTexture()
{
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Images/simulatorBackground.jpg");
    this->backgroundTexture = std::make_unique<sf::Texture>(std::move(backgroundTexture));
}

void SimulatorState::setBackgroundTexture()
{
    this->background.setTexture(*this->backgroundTexture);
}

void SimulatorState::initializationBackground()
{
    this->loadBackgroundTexture();
    this->setBackgroundTexture();
}

void SimulatorState::initializationAssistant()
{
    this->assistant = std::make_unique<GUI::Assistant>(this->getWindow());
}

void SimulatorState::initializationRegistry()
{
    this->registryLabels = {"AL", "BL", "CL", "DL", "AH", "BH", "CH", "DH"};

    for (int i = 0; i < this->registryLabels.size(); i++)
        this->registry.push_back(std::make_unique<Registry>(this->getWindow(), i <= 3 ? 100.f : 350.f, 100.f * ((i % 4) + 1), this->registryLabels[i], i));
}

void SimulatorState::initializationOperationButtonsLabels()
{
    this->operationButtonsLabels = {"MOV", "XCHG", "NOT", "INC", "DEC", "AND", "OR", "XOR", "ADD", "SUB"};
}

void SimulatorState::initializationButtons()
{
    for (int i = 0; i < this->operationButtonsLabels.size(); i++)
        this->buttons.push_back(std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 900.f, 100.f * (i + 1), this->operationButtonsLabels[i]));

    this->buttonsDisplayMethod.push_back(std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 100.f, 1240.f, "Binary"));
    this->buttonsDisplayMethod.push_back(std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 550.f, 1240.f, "Decimal"));
    this->buttonsDisplayMethod.push_back(std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 1000.f, 1240.f, "Hexadecimal"));
}

void SimulatorState::initializationOrder()
{
    this->order = Order::IDLE;
    this->isOrder = false;

    this->first = -1;
    this->second = -1;
}

void SimulatorState::initializationVariables()
{
    this->initializationBackground();
    this->initializationAssistant();
    this->initializationRegistry();
    this->initializationOperationButtonsLabels();
    this->initializationButtons();
    this->initializationOrder();

    this->clickTime = 0;
}

void SimulatorState::updateOrder(const float & dt)
{
    if (this->second == -1)
        for (int i = 0; i < this->registry.size(); i++)
            if (this->registry[i]->getActive() && this->first == -1)
            {
                this->assistant->setText("Select second register");
                this->first = i;
            }
            else if (this->registry[i]->getActive() && this->first != i)
            {
                this->second = i;
            }

    if (this->first != -1 && this->second != -1)
    {
        if (this->order == Order::MOV)
        {
            this->registry[this->first]->setData(this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[0]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::XCHN)
        {
            auto temporaryValue = this->registry[this->first]->getData();
            this->registry[this->first]->setData(this->registry[this->second]->getData());
            this->registry[this->second]->setData(temporaryValue);

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[1]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::AND)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() & this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[5]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::OR)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() | this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[6]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::XOR)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() ^ this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[7]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::ADD)
        {
            std::cout << "ADD!\n";
            this->registry[this->first]->setData(this->registry[this->first]->getData() + this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[8]->use(false);
            this->first = -1;
            this->second = -1;
        }
        else if (this->order == Order::SUB)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() - this->registry[this->second]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[9]->use(false);
            this->first = -1;
            this->second = -1;
        }
    }
    else if (this->first != -1 && this->second == -1)
    {
        if (this->order == Order::NOT)
        {
            this->registry[this->first]->setData(~this->registry[this->first]->getData());

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[2]->use(false);
            this->first = -1;
        }
        else if (this->order == Order::INC)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() + 1);

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[3]->use(false);
            this->first = -1;
        }
        else if (this->order == Order::DEC)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() - 1);

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[4]->use(false);
            this->first = -1;
        }
    }
}

void SimulatorState::deactiveAllRegistry()
{
    for (int i = 0; i < this->registry.size(); i++)
        if (this->registry[i]->getActive())
            this->registry[i]->deactive();
}

bool SimulatorState::isAnyRegistryActive()
{
    for (int i = 0; i < this->registry.size(); i++)
        if (this->registry[i]->getActive())
            return true;
    return false;
}

bool SimulatorState::isAnyButtonUse()
{
    for (int i = 0; i < this->buttons.size(); i++)
        if (this->buttons[i]->getUse())
            return true;
    return false;
}

void SimulatorState::setDisplayMethod(DisplayMethod display)
{
    for (int i = 0; i < this->registry.size(); i++)
        this->registry[i]->setDataDisplay(display);
}

SimulatorState::SimulatorState(sf::RenderWindow * window, std::stack<std::shared_ptr<State>> * states) : State(window, states)
{
    this->initializationVariables();
}

void SimulatorState::update(const float & dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();

    for (int i = 0; i < this->registry.size(); i++)
        this->registry[i]->update(dt);

    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->update(dt);
    
    for (int i = 0; i < this->buttonsDisplayMethod.size(); i++)
        this->buttonsDisplayMethod[i]->update(dt);

    if (!this->isAnyButtonUse() && !this->isAnyRegistryActive())
    {
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(true);
        this->isOrder = false;
        this->order = Order::IDLE;
        this->assistant->setText("Select an instruction");
    }
    else
    {
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(false);
    }

    if (this->buttons[0]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::MOV;
        this->isOrder = true;
        this->buttons[0]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[1]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::XCHN;
        this->isOrder = true;
        this->buttons[1]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[2]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::NOT;
        this->isOrder = true;
        this->buttons[2]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[3]->getActive() && this->letOnClick())
    {
        this->order = Order::INC;
        this->isOrder = true;
        this->buttons[3]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[4]->getActive() && this->letOnClick())
    {
        this->order = Order::DEC;
        this->isOrder = true;
        this->buttons[4]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[5]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::AND;
        this->isOrder = true;
        this->buttons[5]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[6]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::OR;
        this->isOrder = true;
        this->buttons[6]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[7]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::XOR;
        this->isOrder = true;
        this->buttons[7]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[8]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::ADD;
        this->isOrder = true;
        this->buttons[8]->use(true);
        this->assistant->setText("Select the target register");
    }
    else if (this->buttons[9]->getActive())
    {
        this->deactiveAllRegistry();
        this->order = Order::SUB;
        this->isOrder = true;
        this->buttons[9]->use(true);
        this->assistant->setText("Select the target register");
    }

    if (this->buttonsDisplayMethod[0]->getActive() && this->letOnClick())
        this->setDisplayMethod(DisplayMethod::BIN);
    else if (this->buttonsDisplayMethod[1]->getActive() && this->letOnClick())
        this->setDisplayMethod(DisplayMethod::DEC);
    else if (this->buttonsDisplayMethod[2]->getActive() && this->letOnClick())
        this->setDisplayMethod(DisplayMethod::HEX);


    if (isOrder)
        this->updateOrder(dt);

    if (this->clickTime < 0.2f)
        this->clickTime += dt;
}

void SimulatorState::render()
{   
    this->getWindow()->draw(background);

    for (int i = 0; i < this->registry.size(); i++)
        this->registry[i]->render();

    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->render();
    
    for (int i = 0; i < this->buttonsDisplayMethod.size(); i++)
        this->buttonsDisplayMethod[i]->render();

    this->assistant->render();
}

//test function TEST
void SimulatorState::clear()
{
    for (int i = 0; i < this->registry.size(); i++)
        if (this->registry[i]->getActive())
            this->registry[i]->setData(0);
}
