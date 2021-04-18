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

void errorExit(std::string process, std::string exception)
{
    std::cout << "ERROR DURING " << process
        << std::endl << exception
        << std::endl << "Press ENTER to exit...";
    std::cin.get();
}

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
    {
        errorExit("Console initialization", "Console does not support fast output");
        return 1;
    }
        

    Level* level;
    try
    {
        level = new Level("test.lvl.json");
    }
    catch (std::invalid_argument exception)
    {
        errorExit("Level loading", exception.what());
        return 1;
    }
    
    Player player = Player();

    Renderer renderer(player, *level);

    auto previousTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    unsigned const int FOV = 2.0944; // 120 degrees

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
        unsigned const int WALL_HEIGHT = CONSOLE_WIDTH / pow(2, FOV) / 2;

        CHAR_INFO* render = renderer.render(CONSOLE_WIDTH, CONSOLE_HEIGHT, FOV, WALL_HEIGHT);

        const int FPS = 1 / DELTA_TIME;
        std::string title = "Console Ray Caster: FPS - " + std::to_string(FPS) + ", Frame Time - " + std::to_string(DELTA_TIME);
        consoleHandler.setTitle(title.c_str());

        consoleHandler.printChars(render, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);

        delete [] render;
    }
}