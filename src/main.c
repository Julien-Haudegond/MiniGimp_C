#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "histogram.h"


// ./bin/minigimp images/PPM_Base/lake_P6.ppm -h ADDLUM

int main(int argc, char *argv[])
{
	
	if(argc >= 2){
		Image I;
		Image histoInitial;
   		Image histoFinal;
		//vérifier aussi que l'argument dans argv[1] est bien un fichier ppm
		//LoadImage(&I,"images/PPM_Base/lake_P6.ppm");
		LoadImage(&I,argv[1]);
		int displayHistogram = 0;

   		for(int i = 2; i < argc; i++){
   			
   			if(strcmp(argv[i], "ADDCON") == 0){
   				ApplyLut(&I, 50, ADDCON);
   				printf("Ajout de contraste \n");
   			}else if(strcmp(argv[i], "DIMCON") == 0){
   				ApplyLut(&I, 50, DIMCON);
   				printf("Diminution du contraste \n");
   			}else if(strcmp(argv[i], "ADDLUM") == 0){
   				ApplyLut(&I, 50, ADDLUM);
   				printf("Ajout de luminosite \n");
   			}else if(strcmp(argv[i], "DIMLUM") == 0){
   				ApplyLut(&I, 50, DIMLUM);
   				printf("Diminution de la luminosite \n");
   			}else if(strcmp(argv[i], "INVERT") == 0){
   				printf("Inversion des couleurs \n");
   			}else if(strcmp(argv[i], "SEPIA") == 0){
   				printf("Conversion en sepia \n");
   			}else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-histo") == 0){
   				displayHistogram = 1;
   				WriteHistogram(&I, &histoInitial);
   				SaveImage(&histoInitial, "images/test_histo_initial.ppm");	
   			}
   		}
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
    Image histoInitial;
    Image histoFinal;
    LoadImage(&I,"images/PPM_Base/lake_P6.ppm");
    WriteHistogram(&I, &histoInitial);
    SaveImage(&histoInitial, "images/test_histo_initial.ppm");
    ApplyLut(&I, 50, ADDLUM);
    WriteHistogram(&I, &histoFinal);
    SaveImage(&histoFinal, "images/test_histo_final.ppm");
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    FreeImage(&histoInitial);
    FreeImage(&histoFinal);
    return EXIT_SUCCESS;
}

#endif
