#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <string> 
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

    - Maybe use .json for storing level and tile data?
    */

    ConsoleHandler consoleHandler;
    if (!consoleHandler.initialize())
        return 1;

    Level level("test.lvl.json");
    Player player = Player();

    Renderer renderer(player, level);

    auto previousTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    Tile tile("bricks.tl.json");
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            std::cout << tile.sampleTexture((double)x / 8, (double)y / 8, 1).Char.AsciiChar;
        }
        std::cout << std::endl;
    }

    

    /*
    while (true)
    {
        currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> DELTA_TIME_CHRONO = currentTime - previousTime;
        const double DELTA_TIME = DELTA_TIME_CHRONO.count();

        previousTime = currentTime;
        player.update(DELTA_TIME);

        unsigned const int CONSOLE_WIDTH = consoleHandler.getConsoleWidth();
        unsigned const int CONSOLE_HEIGHT = consoleHandler.getConsoleHeight();
        unsigned const int CONSOLE_SIZE = CONSOLE_WIDTH * CONSOLE_HEIGHT;
        CHAR_INFO* render = renderer.render(CONSOLE_WIDTH, CONSOLE_HEIGHT, 2.f, CONSOLE_HEIGHT);

        for (unsigned int i = 0; i < 8; i++)
            render[i].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;

        render[7].Char.AsciiChar = '0' + fmod(DELTA_TIME * 1000000, 1) * 10;
        render[6].Char.AsciiChar = '0' + fmod(DELTA_TIME * 100000, 1) * 10;
        render[5].Char.AsciiChar = '0' + fmod(DELTA_TIME * 10000, 1) * 10;
        render[4].Char.AsciiChar = '0' + fmod(DELTA_TIME * 1000, 1) * 10;
        render[3].Char.AsciiChar = '0' + fmod(DELTA_TIME * 100, 1) * 10;
        render[2].Char.AsciiChar = '0' + fmod(DELTA_TIME * 100, 1) * 10;
        render[1].Char.AsciiChar = '0' + fmod(DELTA_TIME * 10, 1) * 10;
        render[0].Char.AsciiChar = '0' + fmod(DELTA_TIME, 1) * 10;

        for (unsigned int i = 0; i < 5; i++)
            render[i + CONSOLE_WIDTH].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;

        int frameRate = 1 / DELTA_TIME;
        std::string title = "Console Ray Caster: FPS - " + std::to_string(frameRate);
        consoleHandler.setTitle(title.c_str());

        consoleHandler.printChars(render, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);

        delete render;
    }
    */
}