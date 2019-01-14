#include <stdio.h>
#include <stdlib.h>

#define LUTLENGTH 256

#include "lut.h"

void AddLuminosity(Image* I, int intensity){
    int tab[LUTLENGTH];
    int i;

    //Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i + intensity;

        if (tab[i] > 255) tab[i] = 255;
    }

    //Assign the LUT values to the pixel's data
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

    //Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i - intensity;

        if (tab[i] < 0) tab[i] = 0;
    }

    //Assign the LUT values to the pixel's data
    for (i=0; i<(I->w*I->h); i++){
        int value = I->pixel[i].r;
        I->pixel[i].r = tab[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab[value];
    }
}

void AddContrast(Image* I, int intensity){
    int tab[LUTLENGTH];
    int i;
    float coef;

    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Assign a value to a coefficient based on a contrast formula
    coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = coef*(i-128)+128; //Contrast formula

        if (tab[i] < 0) tab[i] = 0;
        if (tab[i] > 255) tab[i] = 255;
    }

    //Assign the LUT values to the pixel's data
    for (i=0; i<(I->w*I->h); i++){
        int value = I->pixel[i].r;
        I->pixel[i].r = tab[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab[value];
    }
}

void ReduceContrast(Image* I, int intensity){
    int tab[LUTLENGTH];
    int i;
    float coef;

    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Take the negative value of the intensity
    //Assign a value to a coefficient based on a contrast formula
    intensity = -intensity;
    coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = coef*(i-128)+128; //Contrast formula

        if (tab[i] < 0) tab[i] = 0;
        if (tab[i] > 255) tab[i] = 255;
    }

    //Assign the LUT values to the pixel's data
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

	if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    switch(chosenLut){
        case ADDLUM: AddLuminosity(I, intensity); break;
        case DIMLUM: ReduceLuminosity(I, intensity); break;
        case ADDCON: AddContrast(I, intensity); break;
        case DIMCON: ReduceContrast(I, intensity); break;
        default: printf("Error\n"); break;
    }
}