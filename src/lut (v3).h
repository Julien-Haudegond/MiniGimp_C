#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef enum {
	ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT, SEPIA
} LUT;

void AddLumLUT(int tab[], int intensity);
void DimLumLUT(int tab[], int intensity);
void AddConLUT(int tab[], int intensity);
void DimConLUT(int tab[], int intensity);

void Apply1DLut (Image* I, int tab[]);
void ApplyLut(Image* I, int intensity, LUT chosenLut);

#endif