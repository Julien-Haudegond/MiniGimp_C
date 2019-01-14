#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"

//MAIN DE TEST (pas définitif)
int main()
{
    Image I;
    LoadImage(&I,"images/PPM_Base/lake_P6.ppm");
    ApplyLut(&I, 50, ADDCON);
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    return EXIT_SUCCESS;
}