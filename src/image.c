#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void NewImage(Image* I, unsigned int w, unsigned int h)
{
	// memory allocation
	I->pixel = calloc(1, w*h*sizeof(Pixel));
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

void LoadImage(Image* I, const char* fichier)
{
	int w, h, max;
	char buffer[10];
	FILE* F = fopen(fichier,"rb");
	if (!F)
		return NULL;
	fscanf(F,"%s %d %d %d\n",buffer,&w,&h,&max);
	NewImage(I,w,h);
    fread(I->pixel, sizeof(Pixel), w*h, F);
	fclose(F);
}

int SaveImage(Image* I, const char* fichier)
{
	int i;
	FILE* F = fopen(fichier,"wb");
	if (!F)
		return -1;
	fprintf(F,"P6\n%d %d\n255\n",I->w,I->h);
	fwrite(I->pixel, sizeof(Pixel), I->w*I->h, F);
	fclose(F);
	return 0;
}