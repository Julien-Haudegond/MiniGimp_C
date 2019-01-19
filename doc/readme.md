# MiniGimp by Mathilde DUMOULIN and Julien HAUDEGOND

## Description

MiniGimp is a little linux command-line program. It permits to apply some effects (primarily **luts**) to an image.
To work, the program needs a P6 PPM image file and a list of effects to apply.

-----------------

## How it works?

Firstly, what you have to do is to convert your image to P6 PPM. To do that, type the next instruction in your terminal :
* convert image.jpg image.ppm * (only if your source image is has a .jpg extension, of course)

Then, you can run the program. If you are in the root folder, you can compile the executable.
* make *

After you just have to type what is written in your terminal.
* ./bin/minigimp image.ppm effect intensity effect intensity ... final_image.ppm *

Here is an expression you can type to test : ** ./bin/minigimp image.ppm ADDLUM 50 ADDCON 25 RED final_image.ppm **

----------------

## List of effects (and how to use them)

There are two types of effects : the **LUTs** and the "destructive" image effects.

### LUTs

* ADDLUM: Add luminosity to your image. Intensity value needs to be between 0 and 100. Example: ADDLUM 30
* DIMLUM: Remove luminosity to your image. Intensity value needs to be between 0 and 100. Example: DIMLUM 25
* ADDCON: Add contrast to your image. Intensity value needs to be between 0 and 100. Example: ADDCON 35
* DIMCON: Flatten your image. Intensity value needs to be between 0 and 100. Example: DIMCON 60
* INVERT: Invert your image. No intensity value required.
* SEPIA: Add a "sepia" effect to your image. No intensity required.
* RED: Turn your image to a red monochrome. No intensity required.
* GREEN: Turn your image to a green monochrome. No intensity required.
* BLUE: Turn your image to a blue monochrome. No intensity required.

### Other effects

* BW: Turn your image to a gray-scaled image. No intensity required.
* FLOP: Left becomes right and vice-versa. No intensity required.
* FLIP: Top becomes bottom and vice-versa. No intensity required.
* FLIPFLOP: Left becomes right and vice-versa. Top becomes bottom and vice-versa. No intensity required.