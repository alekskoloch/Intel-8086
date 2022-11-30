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

void SimulatorState::initializationdisplayMethodDropDownList()
{
    this->displayMethodDropDownList = std::make_unique<GUI::DropDownList>(this->getWindow());
}

void SimulatorState::initializationAssistant()
{
    this->assistant = std::make_unique<GUI::Assistant>(this->getWindow());
}

void SimulatorState::initializationRegistry()
{
    this->registryLabels = {"AL", "BL", "CL", "DL", "AH", "BH", "CH", "DH"};

    for (int i = 0; i < this->registryLabels.size(); i++)
        this->registry.push_back(std::make_unique<Registry>(this->getWindow(), i <= 3 ? 100.f : 350.f, 100.f * ((i % 4) + 1), this->registryLabels[i], 0));

    this->registry.push_back(std::make_unique<Registry>(this->getWindow(), 350.f, 505.f, "MEMORY", 0));
    this->registry[8]->setColor(sf::Color(150,100,30,255));
}

void SimulatorState::initializationOperationButtonsLabels()
{
    this->operationButtonsLabels = {"MOV", "XCHG", "NOT", "INC", "DEC", "AND", "OR", "XOR", "ADD", "SUB"};
}

void SimulatorState::initializationButtons()
{
    for (int i = 0; i < this->operationButtonsLabels.size(); i++)
        this->buttons.push_back(std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 900.f, 100.f * (i + 1), this->operationButtonsLabels[i]));

    this->addressButton = std::make_unique<GUI::Button>(this->getWindow(), ButtonStyle::OPAQUE, 100, 500, "Address");
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
    this->initializationdisplayMethodDropDownList();
    this->initializationAssistant();
    this->initializationRegistry();
    this->initializationOperationButtonsLabels();
    this->initializationButtons();
    this->initializationOrder();

    this->memoryBus = std::make_unique<MemoryBus>();
    this->addressEnter = false;

    this->saveData = false;

    this->clickTime = 0;
    this->textStream = std::make_unique<GUI::TextStream>(this->getWindow());
}

void SimulatorState::updateOrder(const float & dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->first = -1;
        this->second = -1;
    }

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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
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
            this->saveData = true;
        }
        else if (this->order == Order::INC)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() + 1);

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[3]->use(false);
            this->first = -1;
            this->saveData = true;
        }
        else if (this->order == Order::DEC)
        {
            this->registry[this->first]->setData(this->registry[this->first]->getData() - 1);

            this->deactiveAllRegistry();
            this->order = Order::IDLE;
            this->isOrder = false;
            this->buttons[4]->use(false);
            this->first = -1;
            this->saveData = true;
        }
    }

    if (this->addressButton->getString().size() == 4 && this->saveData)
    {
        this->memoryBus->setValue(this->addressButton->getString(), this->registry[8]->getData());
        this->saveData = false;
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

    if (this->addressButton->getString() == "Address")
        for (int i = 0; i < this->registry.size() - 1; i++)
            this->registry[i]->update(dt);
    else
        for (int i = 0; i < this->registry.size(); i++)
            this->registry[i]->update(dt);

    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->update(dt);

    if (this->addressButton->getActive())
        this->addressButton->use(true);

    if (!this->isAnyButtonUse() && !this->isAnyRegistryActive() && !this->addressButton->getUse() && !this->registry[8]->getActive())
    {
        this->textStream->activeTextStream(false);
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(true);
        this->isOrder = false;
        this->order = Order::IDLE;
        if (this->addressButton->getString() == "Address")
            this->assistant->setText("Select registry or an instruction or enter address");
        else
            this->assistant->setText("Select registry or an instruction");
    }
    else if (!this->isAnyButtonUse() && !this->addressButton->getUse() && this->registry[8]->getActive())
    {
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(false);
        this->textStream->activeTextStream(2);
        this->assistant->setText("Enter data to save in memory: " + this->textStream->getText());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            if (this->addressButton->getString().size() == 4)
            {
                this->registry[8]->setData(this->textStream->getText());
                for (int i = 0; i < this->registry.size() - 1; i++)
                    if (this->registry[i]->getActive())
                        this->registry[i]->setData(this->textStream->getText());
                this->memoryBus->setValue(this->addressButton->getString(), this->registry[8]->getData());
            }     

            for (int i = 0; i < this->registry.size(); i++)
                if (this->registry[i]->getActive())
                    this->registry[i]->deactive();

            this->textStream->clear();          
        }
    }
    else if (!this->isAnyButtonUse() && !this->isAnyRegistryActive() && this->addressButton->getUse())
    {
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(false);
        this->textStream->activeTextStream(4);
        this->assistant->setText("Enter address (enter to confirm): " + this->textStream->getText());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            std::string result = this->textStream->getText();

            if (result.size() != 4)
                for (int i = 0; i < 4 - this->textStream->getText().size(); i++)
                    result.insert(0, 1, '0');
                    

            this->registry[8]->setData(this->memoryBus->getValue(result));
            this->addressButton->setString(result);
            this->addressButton->use(false);
            this->textStream->clear();            
        }
    }
    else if (!this->isAnyButtonUse() && this->isAnyRegistryActive())
    {
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(false);
        this->textStream->activeTextStream(2);
        this->assistant->setText("Enter a hexadecimal value (enter to confirm): " + this->textStream->getText());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            if (this->addressButton->getString() != "Address")
            {
                this->memoryBus->setValue(this->addressButton->getString(), this->registry[8]->getData());
            }      

            for (int i = 0; i < this->registry.size(); i++)
                if (this->registry[i]->getActive())
                    this->registry[i]->setData(this->textStream->getText());

            this->textStream->clear();
            for (int i = 0; i < this->registry.size(); i++)
                this->registry[i]->deactive();            
        }
    }
    else
    {
        this->textStream->activeTextStream(false);
        for (int i = 0; i < this->buttons.size(); i++)
            this->buttons[i]->setAvailability(false);
    }

    for (int i = 0; i < this->buttons.size(); i++)
        if (this->buttons[i]->getActive())
        {
            this->deactiveAllRegistry();
            this->order = Order(i + 1);
            this->isOrder = true;
            this->buttons[i]->use(true);
            this->assistant->setText("Select the target register");
        }

    if (this->displayMethodDropDownList->getState() == 1)
        this->setDisplayMethod(DisplayMethod::BIN);
    else if (this->displayMethodDropDownList->getState() == 2)
        this->setDisplayMethod(DisplayMethod::DEC);
    else if (this->displayMethodDropDownList->getState() == 3)
        this->setDisplayMethod(DisplayMethod::HEX);

    this->displayMethodDropDownList->update(dt);

    this->textStream->update(dt);

    this->addressButton->update(dt);

    if (isOrder)
        this->updateOrder(dt);

    if (this->clickTime < 0.2f)
        this->clickTime += dt;
}

void SimulatorState::render()
{   
    this->getWindow()->draw(background);

    if (this->addressButton->getString() == "Address")
        for (int i = 0; i < this->registry.size() - 1; i++)
            this->registry[i]->render();
    else
        for (int i = 0; i < this->registry.size(); i++)
            this->registry[i]->render();

    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->render();
    
    this->addressButton->render();

    this->assistant->render();

    this->displayMethodDropDownList->render();
}
