#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "histogram.h"


int main(int argc, char *argv[])
{
	/* Testing arguments
	for(int j = 0; j < argc ; j++){
		printf("%s \n",argv[j]);
	}*/
	
	if(argc >= 1){
		Image I;
		
		/* 
		char imagesPath[] = "images/PPM_Base/";
		char filename[] = argv[1];
		strcat(imagesPath,filename);
		LoadImage(&I,imagesPath);
		*/
		//vérifier aussi que l'argument dans argv[1] est bien un fichier ppm
		LoadImage(&I,"images/PPM_Base/lake_P6.ppm");

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
   				printf("Diminution luminosite \n");
   			}else if(strcmp(argv[i], "INVERT") == 0){
   				printf("Inversion des couleurs \n");
   			}else if(strcmp(argv[i], "SEPIA") == 0){
   				printf("Image convertie en sepia \n");
   			}
   		}
		SaveImage(&I,"images/test.ppm");
   		FreeImage(&I);
   		return EXIT_SUCCESS;
	}else{
		printf("Missing first argument : input file (filename.ppm) \n");
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
    ApplyLut(&I, 50, DIMCON);
    WriteHistogram(&I, &histoFinal);
    SaveImage(&histoFinal, "images/test_histo_final.ppm");
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    FreeImage(&histoInitial);
    FreeImage(&histoFinal);
    return EXIT_SUCCESS;
}

#endif