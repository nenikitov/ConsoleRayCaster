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

    RayCaster rayCaster(level);
    

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

        for (unsigned int i = 0; i < consoleWidth; i++)
        {
            double angle = player.getAngle() + (double)(i - (double)consoleWidth / 2) / consoleWidth * 2;
            Intersection intersection = rayCaster.findIntersection(player.getPositionX(), player.getPositionY(), angle);

            int ceiling = (float)(consoleHeight) / 2 - consoleHeight / intersection.distance;
            int floor = consoleHeight - ceiling;

            for (unsigned int j = 0; j < consoleHeight; j++)
            {
                if (j < ceiling)
                    screen[j * consoleWidth + i] = ' ';
                else if (j > ceiling && j < floor)
                    screen[j * consoleWidth + i] = '#';
                else
                    screen[j * consoleWidth + i] = '.';
            }
        }
        consoleHandler.printChars(0, 0, screen, consoleWidth * consoleHeight, FOREGROUND_INTENSITY);
    }
}