#include <stdio.h>
#include <stdlib.h>

#include "filters.h"

void blackWhite(Image *img){
    int newvalue;
    for(int i = 0; i < (img->w*img->h); i++){
        newvalue = (img->pixel[i].r + img->pixel[i].g + img->pixel[i].b)/3;
        img->pixel[i].r = newvalue;
        img->pixel[i].g = newvalue;
        img->pixel[i].b = newvalue;
    }
}

void FlopImage(Image* I){
	Image copiedImg;

	NewImage(&copiedImg, I->w, I->h); //Create a new image

	for(int i = 0; i < (I->w*I->h); i++){ //Duplicate the original image
        copiedImg.pixel[i].r = I->pixel[i].r;
        copiedImg.pixel[i].g = I->pixel[i].g;
        copiedImg.pixel[i].b = I->pixel[i].b;
    }

    for(int i = 0; i < (I->h); i++){
    	for(int j = 0; j < (I->w); j++){ //Place the pixels on the lines in the opposite order (from right to left)
    		I->pixel[(i+1)*(I->w)-j].r = copiedImg.pixel[i*(I->w)+j].r; 
    		I->pixel[(i+1)*(I->w)-j].g = copiedImg.pixel[i*(I->w)+j].g;
    		I->pixel[(i+1)*(I->w)-j].b = copiedImg.pixel[i*(I->w)+j].b;
    	}
    }
}

void FlipImage(Image* I){
	Image copiedImg;

	NewImage(&copiedImg, I->w, I->h); //Create a new image

	for(int i = 0; i < (I->w*I->h); i++){ //Duplicate the original image
        copiedImg.pixel[i].r = I->pixel[i].r;
        copiedImg.pixel[i].g = I->pixel[i].g;
        copiedImg.pixel[i].b = I->pixel[i].b;
    }

    for(int i = 0; i < (I->h); i++){
    	for(int j = 0; j < (I->w); j++){ //Place the pixels from bottom to top
    		I->pixel[(I->h-1-i)*(I->w)+j].r = copiedImg.pixel[i*(I->w)+j].r; 
    		I->pixel[(I->h-1-i)*(I->w)+j].g = copiedImg.pixel[i*(I->w)+j].g;
    		I->pixel[(I->h-1-i)*(I->w)+j].b = copiedImg.pixel[i*(I->w)+j].b;
    	}
    }
}

void FlipFlopImage(Image* I){
	FlipImage(I);
	FlopImage(I);
}