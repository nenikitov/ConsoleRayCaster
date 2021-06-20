#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include "Engine/Scene/Scene/Scene.h"
#include "Engine/Render/BufferRenderers/Implemented/SceneRenderer.h"
#include "Engine/Render/RenderLayerComposer/RenderLayerComposer.h"
#include "Engine/Render/Visualizers/Implemented/Console/ASCII/ASCIIVisualizer.h"
#include "Game/SceneObjects/FPSPlayer/FPSPlayer.h"
#include "Engine/Utils/CommandLineArgument/Parser/ArgumentParser.h"

ArgumentParser argumentParser = ArgumentParser();
double resScale = 1.0;
double fov = 2.26893;
std::string renderer = "ascii";
std::string levelName = "test";

void errorExit(std::string process, std::string exception)
{
    std::cout << "ERROR DURING " << process
        << std::endl << exception;

    exit(1);
}

void argHelp()
{
    argumentParser.printHelp("Console Ray Caster", "An application that draws pseudo 3D graphics in console");
    exit(0);
}
void argResScale(std::string out)
{
    try
    {
        resScale = std::stod(out);

        if (resScale < 0.25 || resScale > 2)
            throw std::invalid_argument("");

    }
    catch (std::invalid_argument e)
    {
        errorExit("Reading arguments", "Resolution scale should be a number between 0.25 and 2");
    }
}
void argFov(std::string out)
{
    try
    {
        fov = std::stod(out) * 0.0174533;

        if (fov < 1.0471 || fov > 2.44347)
            throw std::invalid_argument("");

    }
    catch (std::invalid_argument e)
    {
        errorExit("Reading arguments", "Fov should be between 60 and 140 degrees");
    }
}
void argRenderer(std::string out)
{
    if (out == "ASCII" || out == "ascii")
    {
        renderer = "ascii";
    }
    else
    {
        errorExit("Reading arguments", "Unsupported renderer. Please consult --help to see available options");
    }
}
void argLevel(std::string out)
{
    levelName = out;
}



// TODO
// - Code modifications
//     * Add a method to visualizer that will calculate the size of a "window" area that the render layer will be added (so, even with black bars, the render would be in the correct resolution)
//     * Add console line arguments for:
//         - Add REQUIRED field for complex arguments
//         - Add verification, each REQUIRED field should be present
//         - Implement just ADD method to argument parser that accepts both simple and complex
//     * Move all command line argument reading stuff away from main so it is more readable
// - Code cleanup
//     * Comments and docs for new classes
// - Further tasks
//     * Implement simple graphics settings (setting renderer to half resolution) with launch parameters
//     * Implement new cutting-edge 'SHADE' renderer that uses shading characters

int main(int argc, char* argv[])
{
    // Read arguments
    SimpleCommandLineArgument helpArg("help", 'h', "Prints the help message", argHelp);
    ComplexCommandLineArgument resolutionScaleArg("resolution-scale", 's', "Sets the resolution factor of the rendered image (from 0 to 1)", argResScale);
    ComplexCommandLineArgument fovArg("fov", 'f', "Sets the field of view of the camera (from 60 to 140)", argFov);
    ComplexCommandLineArgument rendererArg("renderer", 'r', "Sets the renderer ('ascii' or 'shade')", argRenderer);
    ComplexCommandLineArgument levelArg("level", 'l', "Sets the played level (name of the level file)", argLevel);

    argumentParser.addSimpleArgumentToParser(helpArg);
    argumentParser.addArgumentWithOptionsToParser(resolutionScaleArg);
    argumentParser.addArgumentWithOptionsToParser(fovArg);
    argumentParser.addArgumentWithOptionsToParser(rendererArg);
    argumentParser.addArgumentWithOptionsToParser(levelArg);

    argumentParser.parse(argc, argv);


    IVisualizer* visualizer;
    if (renderer == "ascii")
        visualizer = &ASCIIVisualizer();
    else
        return 1;

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
    const double FONT_RATIO = 0.5;

    Scene scene;
    try
    {
        scene.openLevelFile(levelName);
    }
    catch (std::invalid_argument e)
    {
        errorExit("Level loading", e.what());
    }

    FPSPlayer player(scene, fov);

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
