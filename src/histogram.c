#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

int LumCounter (Image* I){
	long counter[256];
	int i;
	int value;

	//Check if the image exists
    if(!I){
    	printf("No image available.\n");
    	exit(EXIT_FAILURE);
    }

    for(i=0; i<256; i++){
        counter[i] = 0;
    }

	for(i=0; i<(I->w*I->h); i++){
		value = I->pixel[i].r;
		counter[value] += 1;
		value = I->pixel[i].g;
		counter[value] += 1;
		value = I->pixel[i].b;
		counter[value] += 1;
	}

	for(i=0; i<256; i++){
		printf("Y = %d  ==> Nb pixel = %ld\n", i, counter[i]);
	}

	return EXIT_SUCCESS;
}