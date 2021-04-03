#include <chrono>
#include <iostream>
#include <sstream>
#include "Player/Player.h"
#include "Level/Level.h"
#include "ConsoleHandler/ConsoleHandler.h"

int main()
{
    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return -1;

    Level level("test.lvl");
    Player player = Player();

    auto previousTime = std::chrono::system_clock::now();

    for (int i = 0; i < level.tiles.size(); ++i)
    {
        for (int j = 0; j < level.tiles[i].size(); ++j)
        {
            std::cout << level.tiles[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    /*
    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        //consoleHandler.printChars(0, 1, char_type, 10, BACKGROUND_RED);
        player.update(deltaTime);
        //std::cout << "X: " << player.getPositionX() << ", Y: " << player.getPositionY() << ", A: " << player.getAngle() << std::endl;
    }
    */
    
}

void printCharacter(HANDLE handle, SHORT x, SHORT y, const char character[], WORD attributes)
{
    
}