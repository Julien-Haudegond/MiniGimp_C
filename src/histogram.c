#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void LumCounter (Image* I){
	long counter[256];
	int i;
	int value;
	long compteurTEST = 0;

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

	//Transform to percentages
	for(i=0; i<256; i++){
		counter[i] = (counter[i]*100)/(I->w*I->h);
	}



	for(i=0; i<256; i++){
		printf("Y = %d  ==> Nb pixel = %ld\n", i, counter[i]);
	}

	for(i=0; i<256; i++){
		compteurTEST = compteurTEST + counter[i];
	}
	printf("Total de pixels comptabilisés : %ld\n", compteurTEST);

}

/*
int WriteHistogram(Image* I, const char* fichier){
	int w = 256, h = 100; //Dimensions of the histogram's image
	long counter[256]; //Array to count the numbers of pixels per luminance value

	LumCounter(I, counter);

	NewImage(I,w,h);

	for(i=0; i<(I->w*I->h); i++){

	}


}

*/