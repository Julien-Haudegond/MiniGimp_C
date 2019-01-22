#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "image.h"
#include "lut.h"
#include "filters.h"
#include "histogram.h"
#include "arguments.h"

#define MAX_FILENAME 70
int main(int argc, char *argv[])
{
  if(strcmp(checkPPMFile(argv[1]), "ppm") == 0){
    char InitialImagePath[MAX_FILENAME]="./images/PPM_Base/";
    strcat(InitialImagePath,argv[1]);
	
  	if(argc >= 2){
  		Image I;
  		Image histoInitial;
  		Image histoFinal;
      FinalLUT lutF;
      initLutArray(&lutF);
  		LoadImage(&I,InitialImagePath);

      //initialing counters for optional arguments
  		int displayHistogram = 0;
      int chooseFileName = 0;
      int requiredIntensity = 0;
      
  		int intensity;
     		for(int i = 2; i < argc; i++){
          intensity = 0;
          if(strcmp(argv[i], "ADDCON") == 0 || strcmp(argv[i], "DIMCON") == 0 || strcmp(argv[i], "ADDLUM") == 0 || strcmp(argv[i], "DIMLUM") == 0){
            requiredIntensity = 1;
          }
     			if(i<argc-1 && requiredIntensity == 1){
     				intensity = atoi(argv[i+1]);
            //Missing a value after a LUT that is not the last argument
            if(intensity == 0){
              displayMessage(3);
              intensity = 20;
            }
            printf("Intensity : %d \n", intensity);
          //case where a LUT that is supposed to have an intensity value is the last argument
     			}else if(i == argc-1 && requiredIntensity == 1){
              displayMessage(3);
              intensity = 20;
          }
          //Selecting the chosen LUTs
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
            SaveImage(&histoInitial, "images/histo_initial.ppm");
            displayMessage(6);
          }else if(strcmp(argv[i], "-o") == 0){
            if(strcmp(checkPPMFile(argv[i+1]), "ppm") == 0){
              chooseFileName = 1;
              char FinalImagePath[MAX_FILENAME]="./images/";
              strcat(FinalImagePath,argv[i+1]);
              ApplyLutToImage (&I, &lutF);
              SaveImage(&I,FinalImagePath);
            }else{
              displayMessage(2);
              displayExample();
              return EXIT_FAILURE;
            }
            
     			}
  			
  	   	}
      if(chooseFileName != 1){
        ApplyLutToImage (&I, &lutF);
      }
  	  if(displayHistogram == 1){
  			 WriteHistogram(&I, &histoFinal);
  			 SaveImage(&histoFinal, "images/histo_final.ppm");
  			 FreeImage(&histoInitial);
  	     FreeImage(&histoFinal);
  		}
      if(chooseFileName != 1){
        displayMessage(4);
        SaveImage(&I,"images/result.ppm");
      }
  	   	FreeImage(&I);
        displayMessage(5);
  	   	return EXIT_SUCCESS;
  	}
	
  }else{
    displayMessage(1);
    displayExample();
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
