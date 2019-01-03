#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

Image* NewImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->pixel = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

void FreeImage(Image* I)
{
	if (I)
	{
		free(I->pixel);
		free(I);
	}
}

Image* LoadImage(const char* fichier)
{
	int w, h, max;
	char buffer[10];
	Image* I;
	FILE* F = fopen(fichier,"rb");
	if (!F)
		return NULL;
	fscanf(F,"%s %d %d %d\n",buffer,&w,&h,&max);
	I = NewImage(w,h);
    fread(I->pixel, sizeof(Pixel), w*h, F);
	fclose(F);
	return I;
}

int SaveImage(Image* I,const char* fichier)
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