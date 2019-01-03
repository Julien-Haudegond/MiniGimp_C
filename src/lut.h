#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef enum {
	ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT, SEPIA
} LUT;

void AddLuminosity(Image* I, int intensity);
void ReduceLuminosity(Image* I, int intensity);
void ApplyLut(Image* I, int intensity, LUT chosenLut);

#endif