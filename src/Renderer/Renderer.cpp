#include "Renderer.h"

Renderer::Renderer(Player& player, Level& level) : player(player), level(level), rayCaster(RayCaster(level)) {}

CHAR_INFO* Renderer::render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight)
{
    CHAR_INFO* characters = new CHAR_INFO[resolutionX * resolutionY];

    const double PERPENDICULAR_LENGTH = resolutionX / 2.f / tan(fov / 2.f);
    Intersection intersection;

    for (unsigned int x = 0; x < resolutionX; x++)
    {
        const double RAY_OFFSET = (double)x - resolutionX / 2.f;
        const double ANGLE = atan(RAY_OFFSET / PERPENDICULAR_LENGTH);
        
        intersection = this->rayCaster.findIntersection(player.getPositionX(), player.getPositionY(), player.getAngle() + ANGLE);

        if (intersection.intersects)
        {
            const double DELTA_X = intersection.x - player.getPositionX();
            const double DELTA_Y = intersection.y - player.getPositionY();
            const double PROJECTED_DISTANCE = cos(player.getAngle()) * DELTA_X + sin(player.getAngle()) * DELTA_Y;

            const int HEIGHT = abs(wallHeight / PROJECTED_DISTANCE);
            const int CEILING = (resolutionY - HEIGHT) / 2;
            const int FLOOR = CEILING + HEIGHT;

            for (int y = 0; y < resolutionY; y++)
            {
                if (y <= CEILING)
                {
                    characters[y * resolutionX + x].Attributes = ConsoleFGColors::FG_DARK_CYAN;
                    characters[y * resolutionX + x].Char.AsciiChar = '`';
                }
                else if (y >= FLOOR)
                {
                    characters[y * resolutionX + x].Attributes = ConsoleFGColors::FG_GREEN;
                    characters[y * resolutionX + x].Char.AsciiChar = '.';
                }
                else
                {
                    double sampleX = 0;
                    switch (intersection.normalDirection)
                    {
                        case NORTH:
                            sampleX = intersection.x;
                            break;
                        case SOUTH:
                            sampleX = -intersection.x;
                            break;
                        case WEST:
                            sampleX = intersection.y;
                            break;
                        case EAST:
                            sampleX = -intersection.y;
                            break;
                    }

                    double sampleY = (double(y) - CEILING) / HEIGHT;
                    
                    double lightness = 1 - (intersection.distance / 7);

                    CHAR_INFO texure = tile.sampleTexture(sampleX * 2, sampleY * 2, lightness, TileTypes::WALL, intersection.normalDirection);
                    characters[y * resolutionX + x] = texure;
                }
            }
        }
        else
        {
            for (int y = 0; y < resolutionY; y++)
            {
                characters[y * resolutionX + x].Char.AsciiChar = ' ';
                characters[y * resolutionX + x].Attributes = 0;
            }
                
        }
    }

    return characters;
}
