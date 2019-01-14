#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"

//MAIN DE TEST (pas définitif)
int main()
{
    Image I;
    LoadImage(&I,"images/PPM_Base/desert_P6_comments.ppm");
    ApplyLut(&I, 50, ADDLUM);
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    return EXIT_SUCCESS;
}