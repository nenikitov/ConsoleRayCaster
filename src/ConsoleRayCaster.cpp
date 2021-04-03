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

    Level level(std::string("test.lvl"), new std::string[1] {"test"} );
    Player player = Player();

    auto previousTime = std::chrono::system_clock::now();
    char* consoleText = new char[3];

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
    
}

void printCharacter(HANDLE handle, SHORT x, SHORT y, const char character[], WORD attributes)
{
    
}