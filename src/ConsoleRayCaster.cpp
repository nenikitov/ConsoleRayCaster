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

        int frameRate = 1 / deltaTime;
        screen[4] = '0' + frameRate % 10;
        screen[3] = '0' + frameRate / 10 % 10;
        screen[2] = '0' + frameRate / 100 % 10;
        screen[1] = '0' + frameRate / 1000 % 10;
        screen[0] = '0' + frameRate / 10000 % 10;
        consoleHandler.printChars(0, 0, screen, consoleWidth * consoleHeight, FOREGROUND_INTENSITY);




        delete screen;
    }
}