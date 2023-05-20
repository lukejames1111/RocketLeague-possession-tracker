#include "pch.h"
#include "rocketLeaguePossessionTracker.h"
#include <cmath>


BAKKESMOD_PLUGIN(rocketLeaguePossessionTracker, "See who has more possession of the ball", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
std::map<std::string, int> playerTouches;
std::map<int, int> teamTouches;

void rocketLeaguePossessionTracker::onLoad()
{
    _globalCvarManager = cvarManager;
    cvarManager->log("Luke here lol!");

    // Hook to ball touch event
    gameWrapper->HookEventWithCaller<CarWrapper>("Function TAGame.Car_TA.EventHitBall", std::bind(&rocketLeaguePossessionTracker::onBallTouch, this, std::placeholders::_1, std::placeholders::_2));

    gameWrapper->RegisterDrawable(std::bind(&rocketLeaguePossessionTracker::Render, this, std::placeholders::_1));
}

void rocketLeaguePossessionTracker::onBallTouch(CarWrapper car, void* params)
{
    // Get the player's name and team
    auto pri = car.GetPRI();
    if (pri.IsNull())
        return;

    std::string playerName = pri.GetPlayerName().ToString();
    int teamNum = pri.GetTeamNum();

    // Increment player's touch count
    if (playerTouches.count(playerName) == 0)
        playerTouches[playerName] = 0;
    playerTouches[playerName]++;

    // Increment team's touch count
    if (teamTouches.count(teamNum) == 0)
        teamTouches[teamNum] = 0;
    teamTouches[teamNum]++;

    int totalTouches = teamTouches[0] + teamTouches[1];

    std::string logMessage = "Blue Touches: " + std::to_string(teamTouches[0]) + ", Orange Touches: " + std::to_string(teamTouches[1]) + ", Total Touches: " + std::to_string(totalTouches);
    cvarManager->log(logMessage);
}

void rocketLeaguePossessionTracker::Render(CanvasWrapper canvas)
{
    // Set the color to white
    canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
    canvas.SetPosition(Vector2{ 50, 50 });
    canvas.DrawString("Touches");

    // Draw touch count for each player
    int yPosition = 70; // Starting position for y
    for (const auto& player : playerTouches) {
        canvas.SetPosition(Vector2{ 50, yPosition });
        canvas.DrawString(player.first + ": " + std::to_string(player.second));
        yPosition += 20; // Increase y for next string
    }

    // Calculate total touches
    int totalTouches = 0;
    for (const auto& touch : playerTouches) {
        totalTouches += touch.second;
    }

    // Calculate and draw touch count for each team
    for (const auto& team : teamTouches) {
        canvas.SetPosition(Vector2{ 50, yPosition });
        int teamTouchesPercentage = (team.second / static_cast<float>(totalTouches)) * 100.0f;
        canvas.DrawString("Team " + std::to_string(team.first) + " touches: " + std::to_string(team.second) + " (" + std::to_string(teamTouchesPercentage) + "%)");
        yPosition += 20; // Increase y for next string
    }
}



void rocketLeaguePossessionTracker::onUnload()
{
}