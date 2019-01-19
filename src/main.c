#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "filters.h"
#include "histogram.h"


// ./bin/minigimp images/PPM_Base/lake_P6.ppm 

int main(int argc, char *argv[])
{
	
	if(argc >= 2){
		Image I;
		Image histoInitial;
		Image histoFinal;
    FinalLUT lutF;
    initLutArray(&lutF);
		LoadImage(&I,argv[1]);
		int displayHistogram = 0;
		int intensity;
   		for(int i = 2; i < argc; i++){
        intensity = 0;
   			if(i<argc-1){
   				intensity = atoi(argv[i+1]);
   			}
   			if(strcmp(argv[i], "ADDCON") == 0){
   				selectLut(&lutF, intensity, ADDCON);
   			}else if(strcmp(argv[i], "DIMCON") == 0){
   				selectLut(&lutF, intensity, DIMCON);
   			}else if(strcmp(argv[i], "ADDLUM") == 0){
   				selectLut(&lutF, intensity, ADDLUM);
   			}else if(strcmp(argv[i], "DIMLUM") == 0){
   				selectLut(&lutF, intensity, DIMLUM);
   			}else if(strcmp(argv[i], "INVERT") == 0){
          selectLut(&lutF, intensity, INVERT);
        }else if(strcmp(argv[i], "DAYTON") == 0){
          selectLut(&lutF, intensity, DAYTON);
   			}else if(strcmp(argv[i], "RED") == 0){
          selectLut(&lutF, intensity, RED);
        }else if(strcmp(argv[i], "GREEN") == 0){
          selectLut(&lutF, intensity, GREEN);
        }else if(strcmp(argv[i], "BLUE") == 0){
          selectLut(&lutF, intensity, BLUE);
        }else if(strcmp(argv[i], "SEPIA") == 0){
          blackWhite(&I);
          selectLut(&lutF, intensity, SEPIA);
   			}else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-histo") == 0){
   				displayHistogram = 1;
   				WriteHistogram(&I, &histoInitial);
   				SaveImage(&histoInitial, "images/test_histo_initial.ppm");
   			}
			
	   	}
      ApplyLutToImage (&I, &lutF);
	   	if(displayHistogram == 1){
			   WriteHistogram(&I, &histoFinal);
			   SaveImage(&histoFinal, "images/test_histo_final.ppm");
			   FreeImage(&histoInitial);
	       FreeImage(&histoFinal);
		  }
		SaveImage(&I,"images/test.ppm");
	   	FreeImage(&I);

	   	return EXIT_SUCCESS;
	}else{
		printf("Missing argument : input file (filename.ppm)\n");
		return EXIT_FAILURE;
	}
	
}


#ifdef DONTREADTHISCODE

//MAIN DE TEST (pas définitif)
int main()
{
    Image I;
    //Image histoInitial;
    //Image histoFinal;
    FinalLUT lutF;
    initLutArray(&lutF);
    LoadImage(&I,"images/PPM_Base/lake_P6.ppm");
    //WriteHistogram(&I, &histoInitial);
    //SaveImage(&histoInitial, "images/test_histo_initial.ppm");
    //DayToNightLUT(&lutF);
    //ApplyLutToImage(&I, &lutF);

    blackWhite(&I);
    SepiaLUT(&lutF);
    ApplyLutToImage(&I, &lutF);
    //WriteHistogram(&I, &histoFinal);
    //SaveImage(&histoFinal, "images/test_histo_final.ppm");
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    //FreeImage(&histoInitial);
    //FreeImage(&histoFinal);
    return EXIT_SUCCESS;
}

#endif
