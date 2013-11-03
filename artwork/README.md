Textures HOWTO
--------------

Create *grayscale* TGA files with these four colors:

-   `#ffffff`, will be mapped to the "lighter" gray on output
-   `#aaaaaa`, will be mapped to the default gray on output
-   `#555555`, will colored on output
-   `#000000`, will be mapped to the "darker" gray on output

After creating the file, add it to `textures.conf`, use filename without
extension for referencing it in `Rotten::Sprite` class.

Font HOWTO
----------

The current font is generated with `magnum-info`, you need also `FreeTypeFont`
and `MagnumFontConverter` plugins.

    magnum-fontconverter --font FreeTypeFont --converter MagnumFontConverter --atlas-size "64 64" --output-size "64 64" --radius 0 --font-size 6 sources/PressStart2P-Regular.ttf font
