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

        if (intersection.inersects)
        {
            const double DELTA_X = intersection.x - player.getPositionX();
            const double DELTA_Y = intersection.y - player.getPositionY();
            const double PROJECTED_DISTANCE = cos(player.getAngle()) * DELTA_X + sin(player.getAngle()) * DELTA_Y;

            const int HEIGHT = abs(wallHeight / PROJECTED_DISTANCE);
            const int CEILING = (resolutionY - HEIGHT) / 2;
            const int FLOOR = CEILING + HEIGHT;

            for (int y = 0; y < resolutionY; y++)
            {
                if (y < CEILING)
                    renderResult[y * resolutionX + x] = ' ';
                else if (y > FLOOR)
                    renderResult[y * resolutionX + x] = '.';
                else
                {
                    if (intersection.distance < 2)
                        renderResult[y * resolutionX + x] = 219;
                    else if (intersection.distance < 4)
                        renderResult[y * resolutionX + x] = 178;
                    else if (intersection.distance < 6)
                        renderResult[y * resolutionX + x] = 177;
                    else
                        renderResult[y * resolutionX + x] = 176;
                }
            }
        }
        else
        {
            for (int y = 0; y < resolutionY; y++)
                renderResult[y * resolutionX + x] = ' ';
        }
    }

    return renderResult;
}
