#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include "Engine/Scene/Scene/Scene.h"
#include "Engine/Render/BufferRenderers/Implemented/SceneRenderer.h"
#include "Engine/Render/RenderLayerComposer/RenderLayerComposer.h"
#include "Engine/Render/Visualizers/Implemented/ASCII/ASCIIVisualizer.h"
#include "Engine/Render/Visualizers/Implemented/Shade/ShadeVisualizer.h"
#include "Game/SceneObjects/FPSPlayer/FPSPlayer.h"
#include "Engine/Utils/CommandLineArgument/Parser/ArgumentParser.h"

ArgumentParser argumentParser = ArgumentParser();
double resScale = 1.0;
double fov = 2.26893;
double fontRatio = 0.5;
std::string renderer = "ascii";
std::string levelName = "`";

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
void argFontRatio(std::string out)
{
    try
    {
        fontRatio = std::stod(out);

        if (fontRatio < 0.375 || fontRatio > 2)
            throw std::invalid_argument("");

    }
    catch (std::invalid_argument e)
    {
        errorExit("Reading arguments", "Font proportions ratio should be between 0.375 and 2");
    }
}
void argRenderer(std::string out)
{
    if (out == "ASCII" || out == "ascii")
    {
        renderer = "ascii";
    }
    else if (out == "SHADE" || out == "shade")
    {
        renderer = "shade";
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
//     * Move all command line argument reading stuff away from main so it is more readable
// - Code cleanup
//     * Comments and docs for new classes

int main(int argc, char* argv[])
{
    // Read arguments
    SimpleCommandLineArgument helpArg("help", 'h', "Prints the help message", argHelp);
    ComplexCommandLineArgument resolutionScaleArg("resolution-scale", 's', "Sets the resolution factor of the rendered image (from 0.25 for quarter resolution to 2 for double resolution)", false, argResScale);
    ComplexCommandLineArgument fovArg("fov", 'f', "Sets the field of view of the camera (from 60 to 140)", false, argFov);
    ComplexCommandLineArgument fontRatioArg("font-ratio", 'p', "Sets the ratio width/height of the used font to unstretch the image with certain fonts (from 0.375 to 2)", false, argFontRatio);
    ComplexCommandLineArgument rendererArg("renderer", 'r', "Sets the renderer ('ascii' or 'shade')", false, argRenderer);
    ComplexCommandLineArgument levelArg("level", 'l', "Sets the played level (name of the level file)", true, argLevel);

    argumentParser.addArgumentToParser(helpArg);
    argumentParser.addArgumentToParser(resolutionScaleArg);
    argumentParser.addArgumentToParser(fovArg);
    argumentParser.addArgumentToParser(fontRatioArg);
    argumentParser.addArgumentToParser(rendererArg);
    argumentParser.addArgumentToParser(levelArg);

    try
    {
        argumentParser.parse(argc, argv);
    }
    catch (std::invalid_argument e)
    {
        errorExit("Argument reading", e.what());
    }


    AbstractVisualizer* visualizer = nullptr;
    if (renderer == "ascii")
		visualizer = new ASCIIVisualizer();
    else if (renderer == "shade")
        visualizer = new ShadeVisualizer();
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

    SceneRenderer sceneRenderer(renderWidth, renderHeight, fontRatio, scene, player.getCamera());
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
		// std::string title = "Console Ray Caster: FPS - " + std::to_string(FPS) + ", Frame Time - " + std::to_string(DELTA_TIME);
		std::string title = "Console Ray Caster: Coords - " + std::to_string(player.getPosX()) + ", " + std::to_string(player.getPosY());
        if (visualizer != nullptr)
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

        #pragma region Clean up
        for (int i = 0; i < renderHeight; i++)
            delete sceneRenderResult[i];
        delete sceneRenderResult;
        #pragma endregion
    }

	delete visualizer;
}
