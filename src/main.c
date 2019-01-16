#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"

int main(int argc, char *argv[])
{
	/* Testing arguments
	for(int j = 0; j < argc ; j++){
		printf("%s \n",argv[j]);
	}*/
	
	if(argc >= 1){
		Image I;
		//vérifier aussi que l'argument dans argv[1] est bien un fichier ppm
		/* 
		char imagesPath[] = "images/PPM_Base/";
		char filename[] = argv[1];
		strcat(imagesPath,filename);
		LoadImage(&I,imagesPath);
		*/
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

//MAIN DE TEST (pas définitif)
/*
int main()
{
    Image I;
    LoadImage(&I,"images/PPM_Base/lake_P6.ppm");
    ApplyLut(&I, 50, ADDCON);
    SaveImage(&I,"images/test.ppm");
    FreeImage(&I);
    return EXIT_SUCCESS;
}*/