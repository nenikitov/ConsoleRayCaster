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
// - Code modifications
//     * Add a method to visualizer that will calculate the size of a "window" area that the render layer will be added (so, even with black bars, the render would be in the correct resolution)
// - Code cleanup
//     * Comments and docs for new classes
// - Further tasks
//     * Implement simple graphics settings (setting renderer to half resolution) with launch parameters
//     * Implement new cutting-edge 'SHADE' renderer that uses shading characters

int main()
{
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

    const double RENDER_SCALE = 1;
    int renderWidth = int(visualizer.getWidth() * RENDER_SCALE);
    int renderHeight = int(visualizer.getHeight() * RENDER_SCALE);
    const double FOV = 2.26893; // 130 degrees
    const double FONT_RATIO = 0.5;

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
    
    SceneRenderer sceneRenderer(renderWidth, renderHeight, FONT_RATIO, scene, player.getCamera());
    RenderLayerComposer composer(renderWidth, renderHeight);
    
    
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
        const int FPS = int(round(1.f / DELTA_TIME));
        std::string title = "Console Ray Caster: FPS - " + std::to_string(FPS) + ", Frame Time - " + std::to_string(DELTA_TIME);
        visualizer.setTitle(title.c_str());
        #pragma endregion

        #pragma region Update the objects
        player.tick(DELTA_TIME);
        #pragma endregion

        #pragma region Update buffer sizes
        const int VISUALIZER_WIDTH = visualizer.getWidth();
        const int VISUALIZER_HEIGHT = visualizer.getHeight();
        if (VISUALIZER_WIDTH != previousVisualizerWidth || VISUALIZER_HEIGHT != previousVisualizerHeight)
        {
            renderWidth = int(visualizer.getWidth() * RENDER_SCALE);
            renderHeight = int(visualizer.getHeight() * RENDER_SCALE);

            sceneRenderer.changeDimensions(renderWidth, renderHeight);
            composer.changeDimensions(renderWidth, renderHeight);
            previousVisualizerWidth = VISUALIZER_WIDTH;
            previousVisualizerHeight = VISUALIZER_HEIGHT;

            visualizer.refreshSize();
        }
        #pragma endregion

        #pragma region Generate screen buffers and render
        FrameBufferPixel** sceneRenderResult = sceneRenderer.render();
        composer.addRenderLayer(sceneRenderResult, renderWidth, renderHeight, 0, 0, 1, 1);
        visualizer.visualize(composer);
        #pragma endregion

        #pragma region Delete screen buffers
        for (int i = 0; i < renderHeight; i++)
            delete sceneRenderResult[i];
        delete sceneRenderResult;
        #pragma endregion
    }
}
