#include <chrono>
#include <iostream>
#include "Player/Player.h"
#include "Level/Level.h"
#include "ConsoleHandler/ConsoleHandler.h"

int main()
{
    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return -1;

    Level level(std::string("test.lvl"), new std::string[1] {"test"} );
    Player player = Player();

    auto previousTime = std::chrono::system_clock::now();

    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        consoleHandler.printChar(0, 0, "A", BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

        player.update(deltaTime);
        //std::cout << "X: " << player.getPositionX() << ", Y: " << player.getPositionY() << ", A: " << player.getAngle() << std::endl;
    }
    
}

void printCharacter(HANDLE handle, SHORT x, SHORT y, const char character[], WORD attributes)
{
    
}