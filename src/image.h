#ifndef IMAGE_H__
#define IMAGE_H__

#include "pixel.h"

typedef struct Image
{
	unsigned int w,h;
	Pixel* pixel;
} Image;

Image* NewImage(unsigned int w,unsigned int h);
void FreeImage(Image* I);
Image* LoadImage(const char* fichier);
int SaveImage(Image* I,const char* fichier);

#endif