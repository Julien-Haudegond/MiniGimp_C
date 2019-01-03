#ifndef IMAGE_H__
#define IMAGE_H__

#include "pixel.h"

typedef struct Image
{
	int w,h;
	Pixel* pixel;
} Image;

Image* NewImage(int w,int h);
void FreeImage(Image* I);
Image* LoadImage(const char* fichier);
int SaveImage(Image* I,const char* fichier);

#endif