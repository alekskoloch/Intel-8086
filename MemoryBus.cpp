#include "MemoryBus.h"

void MemoryBus::initializationMemoryBus()
{
    this->memoryBus = std::make_unique<std::vector<char>>();
    for (int i = 0; i < this->maxMemory + 1; i++)
        this->memoryBus->push_back(0);
}

void MemoryBus::initializationVariables()
{
    this->initializationMemoryBus();
}

char MemoryBus::getValue(std::string address)
{
    unsigned int result; 
    std::stringstream ss;

    if (address == "")
        address = "0";

    ss << std::hex << address;
    ss >> result;

    return this->memoryBus->at(result);
}

void MemoryBus::setValue(std::string address, char value)
{
    unsigned int result; 
    std::stringstream ss;

    if (address == "")
        address = "0";

    ss << std::hex << address;
    ss >> result;

    std::cout << "SAVE VALUE: " << value << "\n";

    this->memoryBus->at(result) = value;
}

MemoryBus::MemoryBus()
{
    std::cout << "BOOM" << std::endl;
    this->maxMemory = 65535;
    this->initializationVariables();
}
      