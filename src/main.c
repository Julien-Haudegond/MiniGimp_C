#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

//MAIN DE TEST (pas définitif)
int main()
{
    Image* I = LoadImage("lake_P6.ppm");
    SaveImage(I,"test.ppm");
    FreeImage(I);
    return EXIT_SUCCESS;
}