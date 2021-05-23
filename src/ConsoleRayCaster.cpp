#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include "Engine/Scene/Scene/Scene.h"
#include "Engine/Scene/GameObject/Implemented/Player/FPSPlayer.h"
#include "Engine/Render/BufferRenderers/Implemented/SceneRenderer.h"
#include "Engine/Render/RenderLayerComposer/RenderLayerComposer.h"
#include "Engine/Render/Visualizers/Implemented/Console/ASCII/ASCIIVisualizer.h"

void errorExit(std::string process, std::string exception)
{
    std::cout << "ERROR DURING " << process
        << std::endl << exception
        << std::endl << "Press ENTER to exit...";
    std::cin.get();
}

int main()
{
    const int RENDER_WIDTH = 90;
    const int RENDER_HEIGHT = 30;
    const double FOV = 2.0944;

    Scene scene = Scene("test");
    FPSPlayer player = FPSPlayer(scene, FOV);
    
    SceneRenderer sceneRenderer = SceneRenderer(RENDER_WIDTH, RENDER_HEIGHT, scene, player.getCamera());
    RenderLayerComposer composer = RenderLayerComposer(RENDER_WIDTH, RENDER_HEIGHT);
    ASCIIVisualizer visualizer;

    visualizer.init();
    
    
    while (true)
    {
        player.tick(0.01);
        
        FrameBufferPixel** sceneRenderResult = sceneRenderer.render();
        composer.addRenderLayer(sceneRenderResult, RENDER_WIDTH, RENDER_HEIGHT, 0, 0, 1, 1);
        visualizer.render(composer);

        for (int i = 0; i < RENDER_HEIGHT; i++)
            delete sceneRenderResult[i];
        delete sceneRenderResult;
    }
}

/*
  //TODO
  //Major refactoring
  //- Maybe create a struct for rendering result so you can introduce multiple renderers that will transform the result into characters (or pixels in graphics rendering)
  //- Separate game from game engine, so you can create tile and level editors
  //- Resources and not data

ConsoleHandler consoleHandler;
if (!consoleHandler.initialize())
{
    errorExit("Console initialization", "Console does not support fast output");
    return 1;
}


Level* level;
try
{
    level = new Level("test");
}
catch (std::invalid_argument exception)
{
    errorExit("Level loading", exception.what());
    return 1;
}

Player player = Player(level->getPlayerStartX(), level->getPlayerStartY(), level->getPlayerStartAngle());


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

    delete[] render;
}
*/