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

void ApplyLutToImage (Image* I, FinalLUT *lut){
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

//******************************
//********* LUT ARRAYS *********
//******************************

void AddLumLUT(FinalLUT *lut, int intensity){
    if(intensity < 0){
    	fprintf(stderr, "The intensity factor needs to be a positive number\n");
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

void DimLumLUT(FinalLUT *lut, int intensity){
    if(intensity < 0){
    	fprintf(stderr, "The intensity factor needs to be a positive number\n");
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

void AddConLUT(FinalLUT *lut, int intensity){
    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
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

void DimConLUT(FinalLUT *lut, int intensity){
    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
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

void InvertLUT(FinalLUT *lut){
    //Assign to each input value an output value
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i]= 255 - (lut -> tabR[i]);
        lut -> tabG[i]= 255 - (lut -> tabG[i]);
        lut -> tabB[i]= 255 - (lut -> tabB[i]); //Inverting color formula
    }
}

void RedLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabG[i] = 0;
        lut -> tabB[i] = 0;
    }
}

void GreenLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = 0;
        lut -> tabB[i] = 0;
    }
}

void BlueLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = 0;
        lut -> tabG[i] = 0;
    }
}

void DayToNightLUT(FinalLUT *lut){
	DimLumLUT(lut, 80);
	for(int i=0; i<LUTLENGTH; i++){
        lut -> tabR[i] = lut -> tabR[i]/2;
        lut -> tabG[i] = lut -> tabG[i]/2;
    }
}

void blackWhite(Image *img){
    int newvalue;
    for(int i = 0; i < (img->w*img->h); i++){
        newvalue = (img->pixel[i].r + img->pixel[i].g + img->pixel[i].b)/3;
        img->pixel[i].r = newvalue;
        img->pixel[i].g = newvalue;
        img->pixel[i].b = newvalue;
    }
}

void SepiaLUT(FinalLUT *lut){
    for(int i=0; i<LUTLENGTH; i++){
            lut -> tabR[i] = (int)((lut -> tabR[i])*1.4);
            lut -> tabG[i] = (int)((lut -> tabG[i])*1.1);
            lut -> tabB[i] = (int)((lut -> tabB[i])*0.6);
        clippingValues(lut, i);
    }
}




//***************************************
//********* LUT APPLY FUNCTIONS *********
//***************************************




//Function to apply a LUT to a image
void selectLut(FinalLUT *lutF, int intensity, LUT chosenLut){
    switch(chosenLut){
        case ADDLUM: AddLumLUT(lutF, intensity); break;
        case DIMLUM: DimLumLUT(lutF, intensity); break;
        case ADDCON: AddConLUT(lutF, intensity); break;
        case DIMCON: DimConLUT(lutF, intensity); break;
        case INVERT: InvertLUT(lutF);  break;
        case DAYTON: DayToNightLUT(lutF);  break;
        case RED: RedLUT(lutF); break;
        case GREEN: GreenLUT(lutF); break;
        case BLUE: BlueLUT(lutF); break;
        case SEPIA : SepiaLUT(lutF); break;
        default: printf("Error\n"); break;
    }
}
