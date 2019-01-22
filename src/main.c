#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "filters.h"
#include "histogram.h"

#define MAX_FILENAME 70


// ./bin/minigimp images/PPM_Base/lake_P6.ppm 
const char *checkPPMFile(const char *ppmFile){
  //browses filename until it reaches the dot of the extensions
  const char *point = (strrchr(ppmFile,'.'));
  if(!point ||point == ppmFile){
    printf("Unvalid filename for input PPM file \n");
    return "";
  }else{
    printf(point+1);
    return point + 1;
  }
}

void displayMessage(int i){
  switch(i){
    case 1:
    fprintf((stderr), "Unvalid filename for input PPM file \n"); break;
    default : break;
  }
  
}

void displayExample(){
  fprintf((stderr), "Try something like : ./bin/minigimp [PPM_IMAGE_NAME] [LUT_1] [VALUE_1] [LUT_N] [VALUE_N]");
  fprintf((stderr), "LUTS that need an integer parameter [VALUE] : \n ADDCON \n DIMCON \n ADDLUM \n DIMLUM");
  fprintf((stderr), "Following LUTS don't require any extra parameter : \n INVERT \n SEPIA \n RED \n GREEN \n BLUE");
}

  
int main(int argc, char *argv[])
{


  //allocating memory for the string that will contain the path for the initial image
  //int FilenameSize = 1+strlen(argv[1]);
  //char *InitialPPMFile = (char *)malloc(sizeof(char)* FilenameSize);
  char InitialImagePath[MAX_FILENAME]="./images/PPM_Base/";
  //strcat(InitialPPMFile, argv[1]);
  strcat(InitialImagePath,argv[1]);
  //printf("%s",InitialImagePath);

  
  //printf("%s",FinalImagePath);

  //char FinalImagePath[]="images/";

	
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
    
		int intensity;
   		for(int i = 2; i < argc; i++){
        printf("%s \n", argv[i]);
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
        }else if(strcmp(argv[i], "op") == 0){
          chooseFileName = 1;
          char FinalImagePath[MAX_FILENAME]="./images/";
          strcat(FinalImagePath,argv[i+1]);
          printf("%s \n",FinalImagePath);
          ApplyLutToImage (&I, &lutF);
          SaveImage(&I,FinalImagePath);
   			}
			
	   	}
    if(chooseFileName != 1){
      ApplyLutToImage (&I, &lutF);
    }
	  if(displayHistogram == 1){
			 WriteHistogram(&I, &histoFinal);
			 SaveImage(&histoFinal, "images/test_histo_final.ppm");
			 FreeImage(&histoInitial);
	     FreeImage(&histoFinal);
		}
    if(chooseFileName != 1){
      SaveImage(&I,"images/result.ppm");
    }
		  //free(InitialPPMFile);
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
