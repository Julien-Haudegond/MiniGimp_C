#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef enum {
	ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT, SEPIA, RED
} LUT;

void initLutArray(int tab_r[], int tab_g[], int tab_b[]);
void clippingValues(int tab_r[], int tab_g[], int tab_b[], int i);


void AddLumLUT(int tab_r[], int tab_g[], int tab_b[], int intensity);
void DimLumLUT(int tab_r[], int tab_g[], int tab_b[], int intensity);
void AddConLUT(int tab_r[], int tab_g[], int tab_b[], int intensity);
void DimConLUT(int tab_r[], int tab_g[], int tab_b[], int intensity);
void InvertLUT(int tab_r[], int tab_g[], int tab_b[]);
void RedLUT(int tab_r[], int tab_g[], int tab_b[]);

void AssemblyLUT(Image* I, int intensity);
void ApplyLut (Image* I, int tab_r[], int tab_g[], int tab_b[]);



#endif