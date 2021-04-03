#include "Renderer.h"
#include "../Intersection/Intersection.cpp"

Renderer::Renderer(Player& player, Level& level) : player(player), level(level), rayCaster(RayCaster(level)) {}

char* Renderer::render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight)
{
    char* renderResult = new char[resolutionX * resolutionY];
    const double PERPENDICULAR_LENGTH = resolutionX / 2.f / tan(fov / 2.f);
    Intersection intersection;
    for (unsigned int x = 0; x < resolutionX; x++)
    {
        const double RAY_OFFSET = (double)x - resolutionX / 2.f;
        const double ANGLE = atan(RAY_OFFSET / PERPENDICULAR_LENGTH);
        
        intersection = this->rayCaster.findIntersection(player.getPositionX(), player.getPositionY(), player.getAngle() + ANGLE);
        //const double PROJECTED_DISTANCE = 
        
    }

    return renderResult;
}
