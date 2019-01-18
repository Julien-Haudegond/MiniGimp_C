#include <stdio.h>
#include <stdlib.h>

#define LUTLENGTH 256

#include "lut.h"

//******************************
//********* LUT ARRAYS *********
//******************************

void initLutArray(int tab_r[], int tab_g[], int tab_b[]){
	int i;

	for(i=0; i<LUTLENGTH; i++){
	        tab_r[i] = i;
	        tab_g[i] = i;
	        tab_b[i] = i;
	    }
}

void clippingValues(int tab_r[], int tab_g[], int tab_b[], int i){
	if (tab_r[i] < 0) tab_r[i] = 0;
    if (tab_r[i] > 255) tab_r[i] = 255;
    if (tab_g[i] < 0) tab_g[i] = 0;
    if (tab_g[i] > 255) tab_g[i] = 255;
    if (tab_b[i] < 0) tab_b[i] = 0;
    if (tab_b[i] > 255) tab_b[i] = 255;
}


void AddLumLUT(int tab_r[], int tab_g[], int tab_b[], int intensity){
    int i; //Counter for the loop

    if(intensity < 0){
    	fprintf(stderr, "The intensity factor needs to be a positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab_r[i] += intensity;
        tab_g[i] += intensity;
        tab_b[i] += intensity;

        clippingValues(tab_r, tab_g, tab_b, i);
    }
}

void DimLumLUT(int tab_r[], int tab_g[], int tab_b[], int intensity){
    int i; //Counter for the loop

    if(intensity < 0){
    	fprintf(stderr, "The intensity factor needs to be a positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab_r[i] -= intensity;
        tab_g[i] -= intensity;
        tab_b[i] -= intensity;

        clippingValues(tab_r, tab_g, tab_b, i);
    }
}

void AddConLUT(int tab_r[], int tab_g[], int tab_b[], int intensity){
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
        tab_r[i] = coef*(tab_r[i]-128)+128;
        tab_g[i] = coef*(tab_g[i]-128)+128;
        tab_b[i] = coef*(tab_b[i]-128)+128; //Contrast formula

       clippingValues(tab_r, tab_g, tab_b, i);
    }
}

void DimConLUT(int tab_r[], int tab_g[], int tab_b[], int intensity){
    int i; //Counter for the loop
    float coef;

    //Check if the intensity is a positive number
    if(intensity < 0){
    	fprintf(stderr, "Error, the contrast parameter needs to be positive number\n");
    	exit(EXIT_FAILURE);
    }

    //Assign a value to a coefficient based on a contrast formula
    intensity = -intensity;
    coef = (float) (259*(intensity+255))/(255*(259-intensity));

    //Assign to each input value a output value depending on the intensity factor (filling the LUT array)
    for(i=0; i<LUTLENGTH; i++){
        tab_r[i] = coef*(tab_r[i]-128)+128;
        tab_g[i] = coef*(tab_g[i]-128)+128;
        tab_b[i] = coef*(tab_b[i]-128)+128; //Contrast formula

        clippingValues(tab_r, tab_g, tab_b, i);
    }
}

void InvertLUT(int tab_r[], int tab_g[], int tab_b[]){
    //Assign to each input value an output value
    for(int i=0; i<LUTLENGTH; i++){
        tab_r[i]= 255 - tab_r[i];
        tab_g[i]= 255 - tab_g[i];
        tab_b[i]= 255 - tab_b[i]; //Inverting color formula
    }
}

void RedLUT(int tab_r[], int tab_g[], int tab_b[]){
    for(int i=0; i<LUTLENGTH; i++){
        tab_g[i]= 0;
    }
    for(int i=0; i<LUTLENGTH; i++){
        tab_b[i]= 0;
    }
}


/*
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


void AssemblyLUT(Image* I, int intensity){
	int tab_r[LUTLENGTH]; //Create an empty array
    int tab_g[LUTLENGTH]; //Create an empty array
    int tab_b[LUTLENGTH]; //Create an empty array

    //Check if the image exists
	if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    initLutArray(tab_r, tab_g, tab_b);

    //TESTS AVEC DES LUTs PREDEFINIES
	RedLUT(tab_r, tab_g, tab_b);
    AddConLUT(tab_r, tab_g, tab_b, intensity);
    InvertLUT(tab_r, tab_g, tab_b);

    ApplyLut(I, tab_r, tab_g, tab_b);
}

void ApplyLut (Image* I, int tab_r[], int tab_g[], int tab_b[]){
    int value; //Variable used to give the output value based on the input value

    //Check if the image exists
    if(!I){
        printf("No image available.\n");
        exit(EXIT_FAILURE);
    }

    //Assign to each subpixel its new value
    for (int i=0; i<(I->w*I->h); i++){
        value = I->pixel[i].r;
        I->pixel[i].r = tab_r[value];
        value = I->pixel[i].g;
        I->pixel[i].g = tab_g[value];
        value = I->pixel[i].b;
        I->pixel[i].b = tab_b[value];
    }
}


/*
//Function to apply a LUT to a image
void Lut(Image* I, int intensity, LUT chosenLut){
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
        case RED: RedLUT(tab_1, tab_2, tab_3); Apply3DLut(I, tab_1, tab_2, tab_3); break;
        //case SEPIA : SepiaLUT(I); break;
        default: printf("Error\n"); break;
    }
}
*/