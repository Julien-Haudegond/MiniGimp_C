#ifndef LUT_H__
#define LUT_H__
#define LUTLENGTH 256

#include "image.h"

typedef enum {
	ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT, SEPIA, RED, BLUE, GREEN, DAYTON
} LUT;

typedef struct FinalLUT{
    int tabR[LUTLENGTH];
    int tabG[LUTLENGTH];
    int tabB[LUTLENGTH];
}FinalLUT;

void initLutArray(FinalLUT *lut);
void clippingValues(FinalLUT *lut, int i);
void applyLutToImage (Image* I, FinalLUT *lut);
void selectLut(FinalLUT *lutF, int intensity, LUT chosenLut);

void addLumLUT(FinalLUT *lut, int intensity);
void dimLumLUT(FinalLUT *lut, int intensity);
void addConLUT(FinalLUT *lut, int intensity);
void dimConLUT(FinalLUT *lut, int intensity);
void invertLUT(FinalLUT *lut);
void sepiaLUT(FinalLUT *lut);
void redLUT(FinalLUT *lut);
void greenLUT(FinalLUT *lut);
void blueLUT(FinalLUT *lut);
void dayToNightLUT(FinalLUT *lut);

#endif