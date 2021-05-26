#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include "Engine/Scene/Scene/Scene.h"
#include "Engine/Render/BufferRenderers/Implemented/SceneRenderer.h"
#include "Engine/Render/RenderLayerComposer/RenderLayerComposer.h"
#include "Engine/Render/Visualizers/Implemented/Console/ASCII/ASCIIVisualizer.h"
#include "Game/SceneObjects/FPSPlayer/FPSPlayer.h"

void errorExit(std::string process, std::string exception)
{
    std::cout << "ERROR DURING " << process
        << std::endl << exception
        << std::endl << "Press ENTER to exit...";
    std::cin.get();
}

// TODO
// - File structure cleanup
//       + Move FPS player from engine to game directory
//       + Delete old classes
// - Code modifications
//       + Handle exceptions
//       * Make a window that adapts to screen size
//       * Implement more advanced lighting (fullbright texels, sector lighting)
// - Code cleanup
//       * Create general equations in SCENE RENDERER to increase readability
//       * Cleanup in SCENE RENDERER
//       * Find a better way of generating a pointer array than a bunch of switches in ASCII RENDERER
//       * Comments and docs for new classes
// - Further tasks
//       * Implement simple graphics settings (setting renderer to half resolution)
//       * Implement new cutting-edge 'SHADE' renderer that uses shading characters
//       * Finally merge

int main()
{
    const int RENDER_WIDTH = 237; // 237
    const int RENDER_HEIGHT = 63; // 63
    const double FOV = 2.0944;

    Scene scene;
    try
    {
        scene.openLevelFile("test");
    }
    catch (std::invalid_argument e)
    {
        errorExit("Level loading", e.what());
        return 1;
    }

    FPSPlayer player(scene, FOV);
    
    SceneRenderer sceneRenderer(RENDER_WIDTH, RENDER_HEIGHT, scene, player.getCamera());
    RenderLayerComposer composer(RENDER_WIDTH, RENDER_HEIGHT);
    
    ASCIIVisualizer visualizer;
    try
    {
        visualizer.init();
    }
    catch (std::runtime_error e)
    {
        errorExit("Render initialization", e.what());
        return 1;
    }
    
    auto previousTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    int previousVisualizerWidth = 0;
    int previousVisualizerHeight = 0;

    while (true)
    {
        #pragma region Update delta time
        currentTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> DELTA_TIME_CHRONO = currentTime - previousTime;
        const double DELTA_TIME = DELTA_TIME_CHRONO.count();
        previousTime = currentTime;
        #pragma endregion

        #pragma region Set window title
        const int FPS = 1 / DELTA_TIME;
        std::string title = "Console Ray Caster: FPS - " + std::to_string(FPS) + ", Frame Time - " + std::to_string(DELTA_TIME);
        visualizer.setTitle(title.c_str());
        #pragma endregion

        #pragma region Update the objects
        player.tick(DELTA_TIME);
        #pragma endregion

        #pragma region Update buffer sizes
        /*
        const int VISUALIZER_WIDTH = visualizer.getWidth();
        const int VISUALIZER_HEIGHT = visualizer.getHeight();
        if (VISUALIZER_WIDTH != previousVisualizerWidth || VISUALIZER_HEIGHT != previousVisualizerHeight)
        {
            sceneRenderer.changeDimensions(VISUALIZER_WIDTH, VISUALIZER_HEIGHT);
            composer.changeDimensions(VISUALIZER_WIDTH, VISUALIZER_HEIGHT);
            previousVisualizerWidth = VISUALIZER_WIDTH;
            previousVisualizerHeight = VISUALIZER_HEIGHT;
        }
        */
        #pragma endregion

        #pragma region Generate screen buffers and render
        FrameBufferPixel** sceneRenderResult = sceneRenderer.render();
        composer.addRenderLayer(sceneRenderResult, RENDER_WIDTH, RENDER_HEIGHT, 0, 0, 1, 1);
        visualizer.visualize(composer);
        #pragma endregion

        #pragma region Delete screen buffers
        for (int i = 0; i < RENDER_HEIGHT; i++)
            delete sceneRenderResult[i];
        delete sceneRenderResult;
        #pragma endregion
    }
}
