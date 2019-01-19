#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void LuminanceCounter(Image* I, double counter[]){
	int i;
	int value;
	//double compteurTEST = 0;

	//Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    //To initialize all the boxes to 0
    for(i=0; i<256; i++){
        counter[i] = 0;
    }

    //To calculate the meaning luminance value of a pixel and add +1 in the counter array
	for(i=0; i<(I->w*I->h); i++){
		value = ((I->pixel[i].r)+(I->pixel[i].g)+(I->pixel[i].b))/3;
		counter[value] += 1;
	}

	//Transform to percentages then time 1000
	for(i=0; i<256; i++){
		counter[i] = (counter[i]*100)/(I->w*I->h);
		counter[i] *= 1000;
		counter[i] = (long) counter[i];
	}
}


int WriteHistogram(Image* I, Image* Histo){
	int i, j, k;
	int width_times = 6; //Times factor for the histogram's width
	unsigned int width = width_times*256, max_height = 0; //Dimensions of the histogram's image
	double counter[256]; //Array to count the numbers of pixels per luminance value

	//Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

	LuminanceCounter(I, counter);

	//Define the heigth of the histogram (without looking at 0 and 255 because of clipping values)
	for(i=1; i<255; i++){
		if(counter[i] > max_height) max_height = counter[i];
	}

	//Invert the counter in function of the histogram's height
	for(i=0; i<256; i++){
		counter[i] = max_height - counter[i];
	}
	//Create the array with the right dimensions for the histogram
	NewImage(Histo,width,max_height);

	//Fill the histogram array in function of the counter values
	for(i=0; i<(Histo->h); i++){ //Read line by line
		for(j=0; j<256; j++){ //Read column by column
			if (counter[j] <= 0){ //Make a white pixel if the array says it is the moment to put one
				for(k=0; k<width_times/2; k++){ //Permit to have an histogram's width of a multiple of 256 and to draw several times the vertical bars
					Histo->pixel[(i*Histo->w)+(j*width_times+2*k)].r = 255;
					Histo->pixel[(i*Histo->w)+(j*width_times+2*k)].g = 255;
					Histo->pixel[(i*Histo->w)+(j*width_times+2*k)].b = 255;
				}	
			}
			counter[j] -= 1;
		}	
	}

	return EXIT_SUCCESS;
}