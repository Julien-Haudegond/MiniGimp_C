#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void blackWhite(Image *img){
    int newvalue;
    for(int i = 0; i < (img->w*img->h); i++){
        newvalue = (img->pixel[i].r + img->pixel[i].g + img->pixel[i].b)/3;
        img->pixel[i].r = newvalue;
        img->pixel[i].g = newvalue;
        img->pixel[i].b = newvalue;
    }
}