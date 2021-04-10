#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include "Player/Player.h"
#include "Level/Level.h"
#include "ConsoleHandler/ConsoleHandler.h"
#include "RayCaster/RayCaster.h"
#include "Renderer/Renderer.h"

int main()
{
    /*
    TODO
    - Console is a limiting factor here. It can barely handle this many characters written in it, but it breaks as soon as I introduce colors.
    - To fix it, I should implement a framerate cap and rework how the console is handled
    - Also I should pass the wall normal to intersection data
    + Level data is not included in the compiled version, I should figure this out.
    */

    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return -1;

    Level level("test.lvl");
    Player player = Player();

    Renderer renderer(player, level);

    auto previousTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    //for (int i = 0; i < 10000; i++)
    while (true)
    {
        currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> DELTA_TIME_CHRONO = currentTime - previousTime;
        const double DELTA_TIME = DELTA_TIME_CHRONO.count();

        previousTime = currentTime;
        player.update(DELTA_TIME);

        unsigned int consoleWidth = consoleHandler.getConsoleWidth();
        unsigned int consoleHeight = consoleHandler.getConsoleHeight();
        RenderResult render = renderer.render(consoleWidth, consoleHeight, 2.f, consoleHeight);
        char* renderChars = render.characters;
        WORD* renderAttributes = render.attributes;

        renderChars[7] = '0' + fmod(DELTA_TIME * 1000000, 1) * 10;
        renderChars[6] = '0' + fmod(DELTA_TIME * 100000, 1) * 10;
        renderChars[5] = '0' + fmod(DELTA_TIME * 10000, 1) * 10;
        renderChars[4] = '0' + fmod(DELTA_TIME * 1000, 1) * 10;
        renderChars[3] = '0' + fmod(DELTA_TIME * 100, 1) * 10;
        renderChars[2] = '0' + fmod(DELTA_TIME * 100, 1) * 10;
        renderChars[1] = '0' + fmod(DELTA_TIME * 10, 1) * 10;
        renderChars[0] = '0' + fmod(DELTA_TIME, 1) * 10;

        int frameRate = 1 / DELTA_TIME;
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