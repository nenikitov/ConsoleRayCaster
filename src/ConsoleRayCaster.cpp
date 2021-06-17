#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include "Engine/Scene/Scene/Scene.h"
#include "Engine/Render/BufferRenderers/Implemented/SceneRenderer.h"
#include "Engine/Render/RenderLayerComposer/RenderLayerComposer.h"
#include "Engine/Render/Visualizers/Implemented/Console/ASCII/ASCIIVisualizer.h"
#include "Game/SceneObjects/FPSPlayer/FPSPlayer.h"
#include "Engine/Utils/CommandLineArgument/Reader/ArgumentReader.h"

void errorExit(std::string process, std::string exception)
{
    std::cout << "ERROR DURING " << process
           << std::endl << exception;

    exit(1);
}

void readConsoleLineArguments(int argc, char* argv[], std::string& levelName, std::string& renderer, std::string& resScaleString)
{
    /*
    CommandLineArgument argHelp = CommandLineArgument("help", 'h', false);
    CommandLineArgument argLevel = CommandLineArgument("level_name", 'l', true);
    CommandLineArgument argRenderer = CommandLineArgument("renderer", 'r', true);
    CommandLineArgument argResScale = CommandLineArgument("res_scale", 's', true);

    if (ArgumentReader::containsSimple(argc, argv, argHelp))
    {
        std::cout << "Example help page" << std::endl;
        exit(0);
    }

    ArgumentReader::containsWithFollowingArgument(argc, argv, argLevel, levelName);
    ArgumentReader::containsWithFollowingArgument(argc, argv, argRenderer, renderer);
    ArgumentReader::containsWithFollowingArgument(argc, argv, argResScale, resScaleString);
    */
}

// TODO
// - Code modifications
//     * Add a method to visualizer that will calculate the size of a "window" area that the render layer will be added (so, even with black bars, the render would be in the correct resolution)
//     * Add console line arguments for:
//         + Resolution scale
//         . Level file
//         . Render (ASCII, Shade)
//         . Font ratio
//     * Move all command line argument reading stuff away from main so it is more readable
// - Code cleanup
//     * Comments and docs for new classes
// - Further tasks
//     * Implement simple graphics settings (setting renderer to half resolution) with launch parameters
//     * Implement new cutting-edge 'SHADE' renderer that uses shading characters

int main(int argc, char* argv[])
{
    std::string levelName = "test";
    std::string renderer = "ascii";
    std::string resScaleString = "1.0";
    double resScale;


    readConsoleLineArguments(argc, argv, levelName, renderer, resScaleString);

    try
    {
        resScale = std::stod(resScaleString);

        if (resScale < 0.25 || resScale > 2)
            throw std::invalid_argument("");

    }
    catch (std::invalid_argument e)
    {
        errorExit("Reading arguments", "Resolution scale should be a number between 0.25 and 2");
    }


    IVisualizer* visualizer;
    if (renderer == "ASCII" || renderer == "ascii")
    {
        visualizer = &ASCIIVisualizer();
    }
    else
    {
        errorExit("Reading arguments", "Unsupported renderer. Please consult --help to see available options");
    }
    try
    {
        visualizer->init();
    }
    catch (std::runtime_error e)
    {
        errorExit("Render initialization", e.what());
    }


    int renderWidth = int(visualizer->getWidth() * resScale);
    int renderHeight = int(visualizer->getHeight() * resScale);
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
        visualizer->setTitle(title.c_str());
        #pragma endregion

        #pragma region Update the objects
        player.tick(DELTA_TIME);
        #pragma endregion

        #pragma region Update buffer sizes
        const int VISUALIZER_WIDTH = visualizer->getWidth();
        const int VISUALIZER_HEIGHT = visualizer->getHeight();
        if (VISUALIZER_WIDTH != previousVisualizerWidth || VISUALIZER_HEIGHT != previousVisualizerHeight)
        {
            renderWidth = int(visualizer->getWidth() * resScale);
            renderHeight = int(visualizer->getHeight() * resScale);

            sceneRenderer.changeDimensions(renderWidth, renderHeight);
            composer.changeDimensions(renderWidth, renderHeight);
            previousVisualizerWidth = VISUALIZER_WIDTH;
            previousVisualizerHeight = VISUALIZER_HEIGHT;

            visualizer->refreshSize();
        }
        #pragma endregion

        #pragma region Generate screen buffers and render
        FrameBufferPixel** sceneRenderResult = sceneRenderer.render();
        composer.addRenderLayer(sceneRenderResult, renderWidth, renderHeight, 0, 0, 1, 1);
        visualizer->visualize(composer);
        #pragma endregion

        #pragma region Delete screen buffers
        for (int i = 0; i < renderHeight; i++)
            delete sceneRenderResult[i];
        delete sceneRenderResult;
        #pragma endregion
    }
}
