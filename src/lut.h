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
void ApplyLutToImage (Image* I, FinalLUT *lut);

//void initLutArray(int tab_r[], int tab_g[], int tab_b[]);
//void clippingValues(int tab_r[], int tab_g[], int tab_b[], int i);


void AddLumLUT(FinalLUT *lut, int intensity);
void DimLumLUT(FinalLUT *lut, int intensity);
void AddConLUT(FinalLUT *lut, int intensity);
void DimConLUT(FinalLUT *lut, int intensity);
void InvertLUT(FinalLUT *lut);
void SepiaLUT(FinalLUT *lut);
void RedLUT(FinalLUT *lut);
void GreenLUT(FinalLUT *lut);
void BlueLUT(FinalLUT *lut);
void DayToNightLUT(FinalLUT *lut);
void selectLut(FinalLUT *lutF, int intensity, LUT chosenLut);

//void AssemblyLUT(Image* I, int intensity);
//void ApplyLut (Image* I, int tab_r[], int tab_g[], int tab_b[]);



#endif