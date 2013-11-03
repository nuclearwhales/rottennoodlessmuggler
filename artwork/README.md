Textures HOWTO
--------------

Create *grayscale* PNG files in `artwork/` with these four colors:

-   `#ffffff`, will be mapped to the "lighter" gray on output
-   `#aaaaaa`, will be mapped to the default gray on output
-   `#555555`, will colored on output
-   `#000000`, will be mapped to the "darker" gray on output

After creating the file, export it to *grayscale* TGA in `data/` dir and add it
to `data/resources-textures.conf`. There is also `convert.sh` bash script for
batch conversion to TGA. For referencing it in `Rotten::Sprite` class use
filename without extension.

Font HOWTO
----------

The current font is generated with `magnum-info`, you need also `FreeTypeFont`
and `MagnumFontConverter` plugins.

    magnum-fontconverter --font FreeTypeFont --converter MagnumFontConverter --atlas-size "64 64" --output-size "64 64" --radius 0 --font-size 6 sources/PressStart2P-Regular.ttf ../data/font
