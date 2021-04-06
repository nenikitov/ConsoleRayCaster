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

    //for (int i = 0; i < 10000; i++)
    while (true)
    {
        const auto currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> deltaTimeChrono = currentTime - previousTime;
        double deltaTime = deltaTimeChrono.count();
        previousTime = currentTime;

        unsigned int consoleWidth = consoleHandler.getConsoleWidth();
        unsigned int consoleHeight = consoleHandler.getConsoleHeight();
        RenderResult render = renderer.render(consoleWidth, consoleHeight, 2.26893, consoleHeight);
        char* renderChars = render.characters;
        WORD* renderAttributes = render.attributes;


        player.update(deltaTime);

        renderChars[7] = '0' + fmod(deltaTime * 1000000, 1) * 10;
        renderChars[6] = '0' + fmod(deltaTime * 100000, 1) * 10;
        renderChars[5] = '0' + fmod(deltaTime * 10000, 1) * 10;
        renderChars[4] = '0' + fmod(deltaTime * 1000, 1) * 10;
        renderChars[3] = '0' + fmod(deltaTime * 100, 1) * 10;
        renderChars[2] = '0' + fmod(deltaTime * 100, 1) * 10;
        renderChars[1] = '0' + fmod(deltaTime * 10, 1) * 10;
        renderChars[0] = '0' + fmod(deltaTime, 1) * 10;

        int frameRate = 1 / deltaTime;
        renderChars[4 + consoleWidth] = '0' + frameRate % 10;
        renderChars[3 + consoleWidth] = '0' + frameRate / 10 % 10;
        renderChars[2 + consoleWidth] = '0' + frameRate / 100 % 10;
        renderChars[1 + consoleWidth] = '0' + frameRate / 1000 % 10;
        renderChars[0 + consoleWidth] = '0' + frameRate / 10000 % 10;

        consoleHandler.printChars(0, 0, renderChars, renderAttributes, consoleWidth * consoleHeight);

        delete renderChars;
        delete renderAttributes;
    }
    //std::cout << std::endl << "END";
}