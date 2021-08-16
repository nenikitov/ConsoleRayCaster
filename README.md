# Console Ray Caster
This is a rendering engine that uses raycasting to draw pseudo 3D graphics. It outputs the result in console using default 16 colors.

## How does it work
For each column on the screen, the program shoots a ray and finds the closest wall. Knowing the distance between the wall and the virtual camera, we can calculate the visible height. For horizontal surfaces, the program projects the vector between the camera and the wall onto the surface. See **references** for more info.

## Compatibility
I use built-in Windows libraries, so it is Windows only. In future, I might rewrite some parts so it runs on Linux as well. 
It was tested on different Windows terminal applications and I can assure full compatibility with:
* Windows Command Prompt
* Windows PowerShell
* Windows Terminal

## How to edit levels
The levels are stored inside `data/levels/` folder. Level files are essentially `.json` files. The level file should contain the following sections:
* ### **`playerStart`**
    This section contains the start location and rotation of the player.
    * #### `x`
        * `x` coordinate of the player start (1 unit is one cell).
    * #### `y`
        * `y` coordinate of the player start (1 unit is one cell).
    * #### `angle`
        * `angle` of the player in degrees.
* ### **`tile`**
    This section contains the layout of the level.
    * #### `tileLookUp`
        * The look up data which describes what each number in `tileData` corresponds to.
        *  That means that each entry should correspond to the tile name inside the `data/tiles/` folder. This also means that each index inside the `tileData` should have a corresponding entry in `tileLookUp`.
        * It is devided in 3 arrays for wall, floor, and ceiling tiles.
        * The first entry in each section is a special tile. In the `wall`, it is an empty tile which will not be rendered. In the `floor`, it is the "pit" texture, that will be drawn over void floor tiles of index 0. For the `ceiling`, it is the sky texture that will be displayed where ceiling data contains a 0.
    * #### `tileData`
        * The layout of the level. The indexes inside the array are interpreted as tiles using `tileLookUp`.
        * It is divided in 3 arrays for wall, floor, and ceiling tiles. They should all be rectangular arrays with the same dimensions.
* ### **`lighting`**
    This section contains the lighting information.
    * #### `fogDistance`
        * The distance where the fog will be fully "opaque".
    * #### `sectorBrightness`
        * Tthe brightess of each cell from 0 to 7.

## How to edit tiles
The tiles are stored inside `data/tiles/` folder. Tile files are essentially `.json` files. The tile file should contain the following sections:
* ### **`traceVisibility`**
    This describes how the tile reacts to different traces (only applicable for wall tiles).
    * #### `rendering`
        * Should the tile be rendered
    * #### `physics`
        * Should the physics object collide with it
* ### **`rendering`**
    This section describes the information necessary to render the tile. Tile rendering data arrays should be the squares of the same dimensions.
    * #### `brightness`
        * 2D array of values corresponding to the lightness of the texels.
        * It contains values from -7 to 7.
        * 7 for bright and 0 for dark tixels.
        * Negative vales represent fullbright texels (they will be drawn in their original brightness no matter the lighting conditions).
    * #### `colors`
        * 2D array of values corresponding to the color of the texels.
        * It contains values from 0 to 7 (8 possible colors where light/dark variations are automatically selected depending on the tile brightness).
        * The numbers correspond to:
            * ![#808080](https://via.placeholder.com/15/808080?text=+) ![#000000](https://via.placeholder.com/15/000000?text=+) `0` - dark gray / black
            * ![#0000FF](https://via.placeholder.com/15/0000FF?text=+) ![#000080](https://via.placeholder.com/15/000080?text=+) `1` - blue / dark blue
            * ![#00FF00](https://via.placeholder.com/15/00FF00?text=+) ![#008000](https://via.placeholder.com/15/008000?text=+) `2` - green / dark green
            * ![#00FFFF](https://via.placeholder.com/15/00FFFF?text=+) ![#008080](https://via.placeholder.com/15/008080?text=+) `3` - cyan / dark cyan
            * ![#FF0000](https://via.placeholder.com/15/FF0000?text=+) ![#800000](https://via.placeholder.com/15/800000?text=+) `4` - red / dark red
            * ![#FF00FF](https://via.placeholder.com/15/FF00FF?text=+) ![#800080](https://via.placeholder.com/15/800080?text=+) `5` - magenta / dark magenta
            * ![#FFFF00](https://via.placeholder.com/15/FFFF00?text=+) ![#808000](https://via.placeholder.com/15/808000?text=+) `6` - yellow / dark yellow
            * ![#FFFFFF](https://via.placeholder.com/15/FFFFFF?text=+) ![#C0C0C0](https://via.placeholder.com/15/C0C0C0?text=+) `7` - white / light gray

## TODO
* Creating user-friendly editing tools (level and tile editor)

## References
* [Learn more about how raycasting works](https://lodev.org/cgtutor/raycasting.html#:~:text=Raycasting%20is%20a%20rendering%20technique,vertical%20line%20of%20the%20screen. "Raycasting")
* [DDA algorithm I used for faster raycasting](https://www.youtube.com/watch?v=NbSee-XM7WA)
* [Explaination of the raycasting with visuals](https://www.youtube.com/watch?v=eOCQfxRQ2pY)

## Libraries used
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp "JsonCpp Github")
