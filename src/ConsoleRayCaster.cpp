#include <chrono>
#include <iostream>
#include <sstream>
#include "Player/Player.h"
#include "Level/Level.h"
#include "ConsoleHandler/ConsoleHandler.h"
#include "RayCaster/RayCaster.h"

int main()
{
    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return -1;

    Level level("test.lvl");
    Player player = Player();

    auto previousTime = std::chrono::system_clock::now();

    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        unsigned int consoleWidth = consoleHandler.getConsoleWidth();
        unsigned int consoleHeight = consoleHandler.getConsoleHeight();
        char* screen = new char[consoleWidth * consoleHeight];
        screen[consoleWidth * consoleHeight - 1] = '\0';

        player.update(deltaTime);


    }
}