# Console Ray Caster
This is a rendering engine that uses raycasting to draw pseudo 3D graphics. It outputs the rendering result in console.

## Compatibility
It is compatible. This program was tested:
* Windows Command Prompt
* Windows PowerShell
* Windows Terminal

I use built-in Windows libraries, so probably it is not compatible with Linux OS. I did not test it yet. In future, I plan to support it.

## How to edit levels
The levels are stored inside `data/levels/` folder. Level files are essentially `.json` files.
### `player`
This section describes the start location and rotation of the player.
### `tileLookUp`
This section describes what do the indexes mean in the `tileData`. Each index inside the `tileData` should have a corresponding entry in `tileLookUp`. It is devided in 3 arrays for wall, floor, and ceiling tiles. 
### `tileData`
This section describes the layout of the level. The indexes inside the array are interpreted as tiles using `tileLookUp`. It is divided in 3 arrays for wall, floor, and ceiling tiles. They should all have the same dimensions and be rectangular.


## How to edit tiles
The tiles are stored inside `data/tiles/` folder. Tile files are essentially `.json` files.
### `physics`
This section is unused. Will describe the possible interactions between the player and the tile.
### `rendering`
This section describes the information for the rendering. Tile rendering data arrays should be squares of the same dimensions.
#### `brightness`
2D array of values corresponding to the lightness of the texels. It contains values from 0 to 7.
#### `colors`
2D array of values corresponding to the color of the texels. It contains values from 0 to 7 (8 possible colors where light/dark variations are selected depending on the tile orientation). Where:
* ![#000000](https://via.placeholder.com/15/000000?text=+) ![#808080](https://via.placeholder.com/15/808080?text=+) 0 - black / dark gray
* ![#0000FF](https://via.placeholder.com/15/0000FF?text=+) ![#000080](https://via.placeholder.com/15/000080?text=+) 1 - blue / dark blue
* ![#00FF00](https://via.placeholder.com/15/00FF00?text=+) ![#008000](https://via.placeholder.com/15/008000?text=+) 2 - green / dark green
* ![#00FFFF](https://via.placeholder.com/15/00FFFF?text=+) ![#008080](https://via.placeholder.com/15/008080?text=+) 3 - cyan / dark cyan
* ![#FF0000](https://via.placeholder.com/15/FF0000?text=+) ![#800000](https://via.placeholder.com/15/800000?text=+) 4 - red / dark red
* ![#FF00FF](https://via.placeholder.com/15/FF00FF?text=+) ![#800080](https://via.placeholder.com/15/800080?text=+) 5 - magenta / dark magenta
* ![#FFFF00](https://via.placeholder.com/15/FFFF00?text=+) ![#808000](https://via.placeholder.com/15/808000?text=+) 6 - yellow / dark yellow
* ![#FFFFFF](https://via.placeholder.com/15/FFFFFF?text=+) ![#C0C0C0](https://via.placeholder.com/15/C0C0C0?text=+) 7 - white / light gray

## TODO
* Implementing floor and ceiling rendering
* Implementing player interaction (collision / use button)
* Creating user-friendly editing tools (level and tile editor)

## References
[Learn more about how raycasting works](https://lodev.org/cgtutor/raycasting.html#:~:text=Raycasting%20is%20a%20rendering%20technique,vertical%20line%20of%20the%20screen. "Raycasting")

## Libraries used
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp "JsonCpp Github")
