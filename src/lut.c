#include <stdio.h>

#define LUTLENGTH 256

#include "lut.h"

void AddLuminosity(Image* I, int intensity){
    int tab[LUTLENGTH];
    int i;

    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i + intensity;

        if (tab[i] > 255) tab[i] = 255;
    }

    for (i=0; i<(I->w*I->h); i++){
        int value = I->pixel[i].r;
        I->pixel[i].r = tab[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab[value];
    }
}

void ReduceLuminosity(Image* I, int intensity){
    int tab[LUTLENGTH];
    int i;

    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i - intensity;

        if (tab[i] < 0) tab[i] = 0;
    }

    for (i=0; i<(I->w*I->h); i++){
        int value = I->pixel[i].r;
        I->pixel[i].r = tab[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab[value];
    }
}


void ApplyLut(Image* I, int intensity, LUT chosenLut){
    switch(chosenLut){
        case ADDLUM: AddLuminosity(I, intensity); break;
        case DIMLUM: ReduceLuminosity(I, intensity); break;
        default: printf("Error\n"); break;
    }
}