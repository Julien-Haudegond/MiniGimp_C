#include <stdio.h>
#include <stdlib.h>

#define LUTLENGTH 256

#include "lut.h"

/************************
* Functions concerning the final LUT
*************************/

//Initializing the values for the LUT that will contain all combinations
void initLutArray(FinalLUT *lut){
    for(int i =0; i<LUTLENGTH; i++){
            lut -> tabR[i] = i;
            lut -> tabG[i] = i;
            lut -> tabB[i] = i;
        }
}

//Prevent LUT values to be over 255 / under 0
void clippingValues(FinalLUT *lut, int i){
    if (lut -> tabR[i] < 0) lut -> tabR[i] = 0;
    if (lut -> tabR[i] > 255) lut -> tabR[i] = 255;
    if (lut -> tabG[i] < 0) lut -> tabG[i] = 0;
    if (lut -> tabG[i] > 255) lut -> tabG[i] = 255;
    if (lut -> tabB[i] < 0) lut -> tabB[i] = 0;
    if (lut -> tabB[i] > 255) lut -> tabB[i] = 255;
}

void applyLutToImage (Image* I, FinalLUT *lut){
    int value; //Variable used to give the output value based on the input value

    //Check if the image exists
    if(!I){
        printf("No image available.\n");
        exit(EXIT_FAILURE);
    }

    //Assign to each subpixel its new value
    for (int i=0; i<(I->w*I->h); i++){
        value = I->pixel[i].r;
        I->pixel[i].r = lut->tabR[value];
        value = I->pixel[i].g;
        I->pixel[i].g = lut->tabG[value];
        value = I->pixel[i].b;
        I->pixel[i].b = lut->tabB[value];
    }
}

void selectLut(FinalLUT *lutF, int intensity, LUT chosenLut){
    switch(chosenLut){
        case ADDLUM: addLumLUT(lutF, intensity); break;
        case DIMLUM: dimLumLUT(lutF, intensity); break;
        case ADDCON: addConLUT(lutF, intensity); break;
        case DIMCON: dimConLUT(lutF, intensity); break;
        case INVERT: invertLUT(lutF);  break;
        case DAYTON: dayToNightLUT(lutF);  break;
        case RED: redLUT(lutF); break;
        case GREEN: greenLUT(lutF); break;
        case BLUE: blueLUT(lutF); break;
        case SEPIA : sepiaLUT(lutF); break;
        default: printf("Error\n"); break;
    }
}



//******************************
//********* LUT ARRAYS *********
//******************************

void addLumLUT(FinalLUT *lut, int intensity){
    if(intensity < 0 || intensity > 100){
    	fprintf(stderr, "The intensity factor needs to be a number between 0 and 100.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] += intensity;
        lut -> tabG[i] += intensity;
        lut -> tabB[i] += intensity;

        clippingValues(lut, i);
    }
}

void dimLumLUT(FinalLUT *lut, int intensity){
    if(intensity < 0 || intensity > 100){
    	fprintf(stderr, "The intensity factor needs to be a number between 0 and 100.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] -= intensity;
        lut -> tabG[i] -= intensity;
        lut -> tabB[i] -= intensity;

        clippingValues(lut, i);
    }
}

void addConLUT(FinalLUT *lut, int intensity){
    //Check if the intensity is a positive number
    if(intensity < 0 || intensity > 100){
    	fprintf(stderr, "The intensity factor needs to be a number between 0 and 100.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign a value to a coefficient based on a contrast formula
    float coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = coef*((lut -> tabR[i])-128)+128;
        lut -> tabG[i] = coef*((lut -> tabG[i])-128)+128;
        lut -> tabB[i] = coef*((lut -> tabB[i])-128)+128; //Contrast formula
        clippingValues(lut, i);
    }
}

void dimConLUT(FinalLUT *lut, int intensity){
    //Check if the intensity is a positive number
    if(intensity < 0 || intensity > 100){
    	fprintf(stderr, "The intensity factor needs to be a number between 0 and 100.\n");
    	exit(EXIT_FAILURE);
    }

    //Assign a value to a coefficient based on a contrast formula
    intensity = -intensity;
    float coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = coef*((lut -> tabR[i])-128)+128;
        lut -> tabG[i] = coef*((lut -> tabG[i])-128)+128;
        lut -> tabB[i] = coef*((lut -> tabB[i])-128)+128; //Contrast formula
        clippingValues(lut, i);
    }
}

void invertLUT(FinalLUT *lut){
    //Assign to each input value an output value
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i]= 255 - (lut -> tabR[i]);
        lut -> tabG[i]= 255 - (lut -> tabG[i]);
        lut -> tabB[i]= 255 - (lut -> tabB[i]); //Inverting color formula
    }
}

void redLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabG[i] = 0;
        lut -> tabB[i] = 0;
    }
}

void greenLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = 0;
        lut -> tabB[i] = 0;
    }
}

void blueLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = 0;
        lut -> tabG[i] = 0;
    }
}

void dayToNightLUT(FinalLUT *lut){
	dimLumLUT(lut, 20);
	for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = (int) lut -> tabR[i]*0.3;
        lut -> tabG[i] = (int) lut -> tabG[i]*0.4;
        lut -> tabB[i] = (int) lut -> tabB[i]*0.6;
    }
}

void sepiaLUT(FinalLUT *lut){
    dimConLUT(lut, 20);
    for(int i=0; i<LUTLENGTH; i++){
            lut -> tabR[i] = (int)((lut -> tabR[i])*1.2);
            lut -> tabG[i] = (int)((lut -> tabG[i])*1.1);
            lut -> tabB[i] = (int)((lut -> tabB[i])*0.6);
        clippingValues(lut, i);
    }
}