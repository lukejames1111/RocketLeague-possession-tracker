#include "pch.h"
#include "rocketLeaguePossessionTracker.h"


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
}

void rocketLeaguePossessionTracker::onBallTouch(CarWrapper car, void* params)
{
    gameWrapper->RegisterDrawable(std::bind(&rocketLeaguePossessionTracker::Render, this, std::placeholders::_1));

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
    // Draw the bar only if game is active
    if (gameWrapper->IsInGame())
    {
        // Calculate total touches and each team's percentage
        int totalTouches = 0;
        for (const auto& team : teamTouches)
            totalTouches += team.second;

        // Draw touch count for each player and team
        // You need to position these texts at the desired location and style them as you prefer
        for (const auto& player : playerTouches)
            canvas.DrawString(player.first + ": " + std::to_string(player.second));

        for (const auto& team : teamTouches)
            canvas.DrawString("Team " + std::to_string(team.first) + ": " + std::to_string((team.second / (float)totalTouches) * 100.0f) + "%");

        // Draw the bar
        // You need to position and style this as you prefer
        int barHeight = 20;
        int barWidth = canvas.GetSize().X * 0.25; // 25% of screen width
        int totalTouches = teamTouches[0] + teamTouches[1];
        int blueWidth = (teamTouches[0] / (float)totalTouches) * barWidth;
        int orangeWidth = barWidth - blueWidth;

        // Log the calculated values to the console
        std::string logMessage = "Blue Width: " + std::to_string(blueWidth) + ", Orange Width: " + std::to_string(orangeWidth);
        cvarManager->log(logMessage);

        // Draw blue part
        canvas.SetColor(0, 0, 255, 255);
        canvas.FillTriangle(Vector2{ barStartX, barStartY }, Vector2{ barStartX + blueWidth, barStartY }, Vector2{ barStartX, barStartY + barHeight });
        canvas.FillTriangle(Vector2{ barStartX + blueWidth, barStartY }, Vector2{ barStartX, barStartY + barHeight }, Vector2{ barStartX + blueWidth, barStartY + barHeight });

        // Draw orange part
        canvas.SetColor(255, 140, 0, 255);
        canvas.FillTriangle(Vector2{ barStartX + blueWidth, barStartY }, Vector2{ barStartX + barWidth, barStartY }, Vector2{ barStartX + blueWidth, barStartY + barHeight });
        canvas.FillTriangle(Vector2{ barStartX + barWidth, barStartY }, Vector2{ barStartX + blueWidth, barStartY + barHeight }, Vector2{ barStartX + barWidth, barStartY + barHeight });
    }
}

void rocketLeaguePossessionTracker::onUnload()
{
}
