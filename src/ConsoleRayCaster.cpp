#include <chrono>
#include <iostream>
#include <sstream>
#include "Player/Player.h"
#include "Level/Level.h"
#include "ConsoleHandler/ConsoleHandler.h"
#include "RayCaster/RayCaster.h"
#include "Renderer/Renderer.h"

int main()
{
    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return -1;

    Level level("test.lvl");
    Player player = Player();

    Renderer renderer(player, level);

    auto previousTime = std::chrono::system_clock::now();

    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        unsigned int consoleWidth = consoleHandler.getConsoleWidth();
        unsigned int consoleHeight = consoleHandler.getConsoleHeight();
        char* screen = renderer.render(consoleWidth, consoleHeight, 1.5708, consoleHeight);

        player.update(deltaTime);
        consoleHandler.printChars(0, 0, screen, consoleWidth * consoleHeight, FOREGROUND_INTENSITY);


        delete screen;
    }
}