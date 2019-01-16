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
/*
	for(i=0; i<256; i++){
		printf("Y = %d  ==> Nb pixel = %lf\n", i, counter[i]);
	}

	for(i=0; i<256; i++){
		compteurTEST = compteurTEST + counter[i];
	}
	printf("Total de pixels comptabilisés : %lf\n", compteurTEST);
*/

}


int WriteHistogram(Image* I, Image* Histo){
	int i, j;
	int width_times = 6; //Times factor for the histogram's width
	unsigned int width = width_times*256, max_height = 0; //Dimensions of the histogram's image
	double counter[256]; //Array to count the numbers of pixels per luminance value

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
	for(i=0; i<(Histo->h); i++){
		for(j=0; j<256; j++){
			if (counter[j] <= 0){
				Histo->pixel[(i*Histo->w)+(j*width_times)].r = 255;
				Histo->pixel[(i*Histo->w)+(j*width_times)].g = 255;
				Histo->pixel[(i*Histo->w)+(j*width_times)].b = 255;
			}
			counter[j] -= 1;
		}	
	}

	return EXIT_SUCCESS;
}