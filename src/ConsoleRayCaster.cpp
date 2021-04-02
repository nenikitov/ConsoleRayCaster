#include <chrono>
#include <iostream>
#include "Player/Player.h"
#include "Level/Level.h"

int main()
{
    Level level(std::string("test.lvl"), new std::string[1] {"test"} );
    Player player = Player();

    auto previousTime = std::chrono::system_clock::now();

    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        player.update(deltaTime);
        std::cout << "X: " << player.getPositionX() << ", Y: " << player.getPositionY() << ", A: " << player.getAngle() << std::endl;
    }
    
}