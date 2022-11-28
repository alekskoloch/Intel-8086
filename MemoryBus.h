#pragma once

#include "Headers/headers.h"

class MemoryBus
{
private:
    unsigned int maxMemory;
    std::unique_ptr<std::vector<char>> memoryBus;

    void initializationMemoryBus();
    void initializationVariables();
public:

    char getValue(std::string address);
    void setValue(std::string address, char value);

    MemoryBus();


};
  