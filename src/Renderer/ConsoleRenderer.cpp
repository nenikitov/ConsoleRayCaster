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
            const double CEILING = ((double)resolutionY - HEIGHT) / 2;
            const int FLOOR = CEILING + HEIGHT;

            int lastTexturedFloor = 0;
            for (int y = 0; y < resolutionY; y++)
            {
                if (y < CEILING)
                {
                    #pragma region Ceiling rendering
                    characters[y * resolutionX + x].Attributes = ConsoleFGColors::FG_DARK_CYAN;
                    characters[y * resolutionX + x].Char.AsciiChar = '`';
                    #pragma endregion
                }
                else if (y > FLOOR)
                {
                    #pragma region Floor rendering
                    // Calculate vertical angle of the pixel
                    const double VERT_ANGLE = (y - HALF_HEIGHT) / (double)resolutionY * HALF_VER_FOV;
                    // Calculate ratio of distances between floor texel and wall intersection
                    const double PROJECTION_RATIO = (wallHeight / 2 / tan(VERT_ANGLE)) / PROJECTED_DISTANCE / resolutionX;
                    // Project the point into world space
                    double floorX = player.getPositionX() + DELTA_X * PROJECTION_RATIO;
                    double floorY = player.getPositionY() + DELTA_Y * PROJECTION_RATIO;
                    // Find tile
                    int tileIndex = level.floorIndexAt(floorX, floorY);
                    CHAR_INFO texture;

                    
                    if (tileIndex != 0)
                    {
                        Tile tile = level.floorTileFrom(tileIndex);
                        // Sample the texture
                        double sampleX = floorY;
                        double sampleY = -floorX;
                        texture = tile.sampleTexture(sampleX, sampleY, TileTypes::FLOOR);
                        lastTexturedFloor = y;
                    }
                    else
                    {
                        texture.Attributes = ConsoleFGColors::FG_DARK_GRAY;
                        const double VOID_RATIO = ((double)y - lastTexturedFloor) / VERT_ANGLE / resolutionY;
                        if (VOID_RATIO < 1.25)
                            texture.Char.AsciiChar = '\'';
                        else if (VOID_RATIO < 1.75)
                            texture.Char.AsciiChar = '`';
                        else
                            texture.Char.AsciiChar = ' ';
                    }
                    // Put it
                    characters[y * resolutionX + x] = texture;
                    #pragma endregion
                }
                else
                {
                    #pragma region Wall rendering
                    // Find the point where the texture should be sampled
                    double sampleY = ((double)y - CEILING) / ((double)HEIGHT + 1);
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
                    CHAR_INFO texture = tile.sampleTexture(sampleX, sampleY, lightness, TileTypes::WALL, intersection.normalDirection);
                    // Put it
                    characters[y * resolutionX + x] = texture;
                    lastTexturedFloor = y;
                    #pragma endregion
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
