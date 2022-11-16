#pragma once

#include "../Headers/headers.h"

class GraphicsSettings
{
public:
    std::string windowTitle;
    unsigned windowWidth;
    unsigned windowHeight;
    unsigned windowFrameRateLimit;
    
    GraphicsSettings();

    void initializationGraphicsSettings();

    void loadGraphicsSettingsFromFile(const std::string & graphicsSettingsFilePath);
};