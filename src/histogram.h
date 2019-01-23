#ifndef HISTOGRAM_H__
#define HISTOGRAM_H__

#include "image.h"

void luminanceCounter(Image* I, double counter[]);
int writeHistogram(Image* I, Image* Histo);

#endif