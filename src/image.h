#ifndef IMAGE_H__
#define IMAGE_H__

#include "pixel.h"

typedef struct Image
{
	unsigned int w,h;
	Pixel* pixel;
} Image;

void NewImage(Image* I, unsigned int w, unsigned int h);
void FreeImage(Image* I);
int LoadImage(Image* I, const char* fichier);
int SaveImage(Image* I, const char* fichier);

#endif