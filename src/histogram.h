#ifndef HISTOGRAM_H__
#define HISTOGRAM_H__

#include "image.h"

void LuminanceCounter(Image* I, double counter[]);
int WriteHistogram(Image* I, Image* Histo);

#endif