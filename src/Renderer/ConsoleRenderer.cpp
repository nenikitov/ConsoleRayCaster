#include "ConsoleRenderer.h"

Renderer::Renderer(Player& player, Level& level) : player(player), level(level), rayCaster(RayCaster(level)) {}

CHAR_INFO* Renderer::render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight)
{
    #pragma region Precalculate and initialize needed values
    CHAR_INFO* characters = new CHAR_INFO[resolutionX * resolutionY];

    // Used for perspective correction
    const double PERPENDICULAR_LENGTH = resolutionX / 2.f / tan(fov / 2.f);
    const double HALF_VER_FOV = 0.5 * fov / (double)resolutionX * (double)resolutionY;
    Intersection intersection;
    #pragma endregion

    // Render column by column
    for (unsigned int x = 0; x < resolutionX; x++)
    {
        // Angle of the ray from the X position
        const double RAY_OFFSET = (double)x - resolutionX / 2.f;
        const double HOR_ANGLE = atan(RAY_OFFSET / PERPENDICULAR_LENGTH);
        const double HALF_HEIGHT = resolutionY / 2.f;
        
        // Find intersection
        intersection = this->rayCaster.findIntersection(player.getPositionX(), player.getPositionY(), player.getAngle() + HOR_ANGLE);

        if (intersection.intersects)
        {
            // If the intersection happens, render the walls
            const double DELTA_X = intersection.x - player.getPositionX();
            const double DELTA_Y = intersection.y - player.getPositionY();
            // Fix the fisheye effect
            const double PROJECTED_DISTANCE = cos(player.getAngle()) * DELTA_X + sin(player.getAngle()) * DELTA_Y;
            // The heights of the wall, ceiling and floor
            const int HEIGHT = abs(wallHeight / PROJECTED_DISTANCE);
            const int CEILING = (resolutionY - HEIGHT) / 2;
            const int FLOOR = CEILING + HEIGHT;

            for (int y = 0; y < resolutionY; y++)
            {
                if (y <= CEILING)
                {
                    // Ceiling rendering
                    characters[y * resolutionX + x].Attributes = ConsoleFGColors::FG_DARK_CYAN;
                    characters[y * resolutionX + x].Char.AsciiChar = '`';
                }
                else if (y >= FLOOR)
                {
                    const double VERT_ANGLE = (y - HALF_HEIGHT) / (double)resolutionY * HALF_VER_FOV;
                    const double PROJECTION_RATIO = PROJECTED_DISTANCE / (wallHeight / 2 / tan(VERT_ANGLE));
                    double sampleX = player.getPositionX() + (player.getPositionX() - intersection.x) * PROJECTION_RATIO;
                    double sampleY = player.getPositionY() + (player.getPositionY() - intersection.y) * PROJECTION_RATIO;
                    CHAR_INFO texture = testTile.sampleTexture(sampleX, sampleY, TileTypes::FLOOR);
                    // Floor rendering
                    characters[y * resolutionX + x].Attributes = ConsoleFGColors::FG_DARK_GREEN;

                    
                    if (PROJECTION_RATIO < 0.01)
                        characters[y * resolutionX + x].Char.AsciiChar = '@';
                    else if (PROJECTION_RATIO < 0.04)
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    else if (PROJECTION_RATIO < 0.06)
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    else if (PROJECTION_RATIO < 0.08)
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    else if (PROJECTION_RATIO < 0.1)
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    else if (PROJECTION_RATIO < 0.15)
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    else
                        characters[y * resolutionX + x].Char.AsciiChar = '`';
                    
                }
                else
                {
                    // Wall rendering
                    // Find the point where the texture should be sampled
                    double sampleY = (double(y) - CEILING) / HEIGHT;
                    double sampleX = 0;
                    switch (intersection.normalDirection)
                    {
                        case NORTH:
                            sampleX = -intersection.x;
                            break;
                        case SOUTH:
                            sampleX = intersection.x;
                            break;
                        case WEST:
                            sampleX = intersection.y;
                            break;
                        case EAST:
                            sampleX = -intersection.y;
                            break;
                    }
                    // Other info for texture sampling
                    double lightness = 1 - (intersection.distance / 7);
                    Tile tile = level.wallTileFrom(intersection.tile);
                    // Sample the textures
                    CHAR_INFO texure = tile.sampleTexture(sampleX, sampleY, lightness, TileTypes::WALL, intersection.normalDirection);
                    // Put it
                    characters[y * resolutionX + x] = texure;
                }
            }
        }
        else
        {
            // If the intersection happens, render empty characters
            for (int y = 0; y < resolutionY; y++)
            {
                characters[y * resolutionX + x].Char.AsciiChar = ' ';
                characters[y * resolutionX + x].Attributes = 0;
            } 
        }
    }

    return characters;
}
