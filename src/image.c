#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void NewImage(Image* I, unsigned int w, unsigned int h)
{
	//Memory allocation
	I->pixel = calloc(1, w*h*sizeof(Pixel));
	if (I->pixel == NULL){
		fprintf(stderr, "Error: not enough memory.\n");
		exit(EXIT_FAILURE);
	}
	//Width and heigth attribution
	I->w = w;
	I->h = h;
}

//Free the allocated memory
void FreeImage(Image* I)
{
	if (I)
	{
		free(I->pixel);
	}
}

int LoadImage(Image* I, const char* fichier)
{
	int w, h, maxDepth, reader;
	char magicNumber[10];

	//Open a file
	FILE* F = fopen(fichier,"rb");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	//Read the PPM Magic Number
	if(fscanf(F,"%s\n", magicNumber) != 1){
		fprintf(stderr, "Error during the header reading.\n");
		exit(EXIT_FAILURE);
	}

	//Check if the file is a P6 PPM
	if(magicNumber[0] != 'P' || magicNumber[1] != '6'){
		fprintf(stderr, "The file is not a P6 PPM.\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments
	reader = getc(F);
	//If the first character is a #, it reads the whole line and go to the next one
	while (reader == '#'){
		while(getc(F) != '\n');
		reader = getc(F);
	}
	ungetc(reader, F);
	
	//Read the width, height and maximum color depth.
	if(fscanf(F,"%d %d %d\n",&w,&h,&maxDepth) != 3){
		fprintf(stderr, "Error during dimensions reading.\n");
		exit(EXIT_FAILURE);
	}

	//Create a new image (array) with the right dimensions ; read the values of the PPM and store them in the empty array
	NewImage(I,w,h);
    if(fread(I->pixel, sizeof(Pixel), w*h, F) != w*h){
    	fprintf(stderr, "Error: the image was not read completely.\n");
    	exit(EXIT_FAILURE);
    }
	fclose(F);
	return EXIT_SUCCESS;
}

int SaveImage(Image* I, const char* fichier)
{
	//Create a new file
	FILE* F = fopen(fichier,"wb");
	if (!F){
		fprintf(stderr, "Unable to save the file.\n");
		exit(EXIT_FAILURE);
	}

	//Write the header
	fprintf(F,"P6\n%d %d\n255\n",I->w,I->h);

	//Write the data
	fwrite(I->pixel, sizeof(Pixel), I->w*I->h, F);
	
	fclose(F);
	return EXIT_SUCCESS;
}