#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class rocketLeaguePossessionTracker : public BakkesMod::Plugin::BakkesModPlugin
{
    int totalTouches;  // Add this line to declare totalTouches as a member variable

    //Boilerplate
    virtual void onLoad();
    virtual void onUnload();
    void onBallTouch(CarWrapper car, void* params);
    void Render(CanvasWrapper canvas);
};
