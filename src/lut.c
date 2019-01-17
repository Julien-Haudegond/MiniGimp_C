#include <stdio.h>
#include <stdlib.h>

#define LUTLENGTH 256

#include "lut.h"

//******************************
//********* LUT ARRAYS *********
//******************************


void AddLumLUT(int tab[], int intensity){
    int i; //Counter for the loop

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i + intensity;

        if (tab[i] > 255) tab[i] = 255;
    }
}

void DimLumLUT(int tab[], int intensity){
    int i; //Counter for the loop

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab[i] = i - intensity;

        if (tab[i] < 0) tab[i] = 0;
    }
}

void AddConLUT(int tab[], int intensity){
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
}

void DimConLUT(int tab[], int intensity){
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
}

void InvertLUT(int tab[]){
    //Assign to each input value an output value
    for(int i=0; i<LUTLENGTH; i++){
        tab[i]= i - 255; //Inverting color formula
        if(tab[i]<0) tab[i] = -tab[i];
    }
}

void SepiaLUT(int tab1[], int tab2[], int tab3[]){
    int value; int change = 0;
    for (int i=0; i<(I->w*I->h); i++){
        value = (I->pixel[i].r + I->pixel[i].g + I->pixel[i].b)/3 ;
        if (value > 40 && value < 225){
            change = 20;
        }
        I->pixel[i].r = value + 10;
        I->pixel[i].g = value;
        I->pixel[i].b = value - change;
        change = 0;
    }
}

/*
void SepiaLUT(Image* I){
    for(int i=0; i<LUTLENGTH; i++){
        tab[i] = tab[i]-255; //Invert colors formula
        if (tab[i] < 0) tab[i] = - tab[i];
        if (tab[i] > 255) tab[i] = 255;
    }
   
    BWLUT(I);
    
    for (int i=0; i<(I->w*I->h); i++){
        //I->pixel[i].b = I->pixel[i].b + 20;
       // I->pixel[i].r = I->pixel[i].r + 50;
        
        if(I->pixel[i].b < 0){
            I->pixel[i].b = 0;
        }
        if(I->pixel[i].r > 255){
            I->pixel[i].b = 255;
        }
    }
}*/





//***************************************
//********* LUT APPLY FUNCTIONS *********
//***************************************


//Function to apply a 1D LUT to a image
void Apply1DLut (Image* I, int tab[]){
    int value; //Variable used to give the output value based on the input value

    //Check if the image exists
    if(!I){
        printf("No image available.\n");
        exit(EXIT_FAILURE);
    }

    //Assign to each subpixel its new value
    for (int i=0; i<(I->w*I->h); i++){
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
    int tab_1[LUTLENGTH]; //Create an empty array
    int tab_2[LUTLENGTH]; //Create an empty array
    int tab_3[LUTLENGTH]; //Create an empty array
    

    //Check if the image exists
	if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    switch(chosenLut){
        case ADDLUM: AddLumLUT(tab_1, intensity); Apply1DLut (I, tab_1); break;
        case DIMLUM: DimLumLUT(tab_1, intensity); Apply1DLut (I, tab_1); break;
        case ADDCON: AddConLUT(tab_1, intensity); Apply1DLut (I, tab_1); break;
        case DIMCON: DimConLUT(tab_1, intensity); Apply1DLut (I, tab_1); break;
        case INVERT: InvertLUT(tab_1); Apply1DLut (I, tab_1); break;
        case SEPIA : SepiaLUT(I); break;
        default: printf("Error\n"); break;
    }
}