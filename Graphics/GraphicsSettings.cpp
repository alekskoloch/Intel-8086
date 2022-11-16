#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    loadGraphicsSettingsFromFile("Graphics\\graphics_settings.ini");
}

void GraphicsSettings::initializationGraphicsSettings()
{
    this->windowTitle = "Intel 8086";
    this->windowWidth = 800;
    this->windowHeight = 800;
    this->windowFrameRateLimit = 60;
}

void GraphicsSettings::loadGraphicsSettingsFromFile(const std::string & graphicsSettingsFilePath)
{
    std::ifstream inputFileStream(graphicsSettingsFilePath);

    if (inputFileStream)
    {
        std::getline(inputFileStream, this->windowTitle);
        inputFileStream >> this->windowWidth >> this->windowHeight;
        inputFileStream >> this->windowFrameRateLimit;
    }
    else
        initializationGraphicsSettings();
}