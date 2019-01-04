#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void NewImage(Image* I, unsigned int w, unsigned int h)
{
	// memory allocation
	I->pixel = calloc(1, w*h*sizeof(Pixel));
	if (I->pixel == NULL){
		printf("Error: not enough memory.\n");
		exit(EXIT_FAILURE);
	}
	I->w = w;
	I->h = h;
}

void FreeImage(Image* I)
{
	if (I)
	{
		free(I->pixel);
	}
}

int LoadImage(Image* I, const char* fichier)
{
	int w, h, max;
	char buffer[10];
	FILE* F = fopen(fichier,"rb");
	if (!F)
		return EXIT_FAILURE;
	if(fscanf(F,"%s %d %d %d\n",buffer,&w,&h,&max) != 4){
		printf("Error on the header reading.\n");
		exit(EXIT_FAILURE);
	}
	NewImage(I,w,h);
    if(fread(I->pixel, sizeof(Pixel), w*h, F) != w*h){
    	printf("Error: the image was not read completely.\n");
    	exit(EXIT_FAILURE);
    }
	fclose(F);
	return EXIT_SUCCESS;
}

int SaveImage(Image* I, const char* fichier)
{
	FILE* F = fopen(fichier,"wb");
	if (!F)
		return EXIT_FAILURE;
	fprintf(F,"P6\n%d %d\n255\n",I->w,I->h);
	fwrite(I->pixel, sizeof(Pixel), I->w*I->h, F);
	fclose(F);
	return EXIT_SUCCESS;
}