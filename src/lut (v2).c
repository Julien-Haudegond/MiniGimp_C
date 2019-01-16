#include <stdio.h>
#include <stdlib.h>

#define LUTLENGTH 256

#include "lut.h"

//******************************
//********* LUT ARRAYS *********
//******************************


int* AddLumLUT(int tab[], int intensity){
    int i; //Counter for the loop

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i + intensity;

        if (tab[i] > 255) tab[i] = 255;
    }

    return tab;
}

int* DimLumLUT(int tab[], int intensity){
    int i; //Counter for the loop

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i - intensity;

        if (tab[i] < 0) tab[i] = 0;
    }

    return tab;
}

int* AddConLUT(int tab[], int intensity){
    int i; //Counter for the loop
    float coef;

    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Assign a value to a coefficient based on a contrast formula
    coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = coef*(i-128)+128; //Contrast formula

        if (tab[i] < 0) tab[i] = 0;
        if (tab[i] > 255) tab[i] = 255;
    }

    return tab;
}

int* DimConLUT(int tab[], int intensity){
    int i; //Counter for the loop
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

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = coef*(i-128)+128; //Contrast formula

        if (tab[i] < 0) tab[i] = 0;
        if (tab[i] > 255) tab[i] = 255;
    }

    return tab;
}



//***************************************
//********* LUT APPLY FUNCTIONS *********
//***************************************


//Function to apply a 1D LUT to a image
void Apply1DLut (Image* I, int tab[]){
    int i;
    int value; //Variable used to give the output value based on the input value

    //Check if the image exists
    if(!I){
        printf("No image available.\n");
        exit(EXIT_FAILURE);
    }

    //Assign to each subpixel its new value
    for (i=0; i<(I->w*I->h); i++){
        value = I->pixel[i].r;
        I->pixel[i].r = tab[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab[value];
    }
}

//Function to apply a LUT to a image
void ApplyLut(Image* I, int intensity, LUT chosenLut){
    int tab[LUTLENGTH]; //LUT Array

	if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    switch(chosenLut){
        case ADDLUM: Apply1DLut (I, AddLumLUT(tab, intensity)); break;
        case DIMLUM: Apply1DLut (I, DimLumLUT(tab, intensity)); break;
        case ADDCON: Apply1DLut (I, AddConLUT(tab, intensity)); break;
        case DIMCON: Apply1DLut (I, DimConLUT(tab, intensity)); break;
        default: printf("Error\n"); break;
    }
}