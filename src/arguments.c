#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arguments.h"

const char *checkPPMFile(const char *ppmFile){
  //browses filename until it reaches the dot of the extensions
  const char *point = (strrchr(ppmFile,'.'));
  if(!point ||point == ppmFile){
    return "";
  }else{
    //returns whats after the dot, if it's "ppm"
    return point + 1;
  }
}

void displayMessage(int i){
  switch(i){
    case 1:
    fprintf((stderr), "Missing/Unvalid filename for input PPM file \n"); break;
    case 2:
    fprintf((stderr), "Unvalid filename for output PPM file \n"); break;
    case 3:
    fprintf((stderr),"Missing a value argument for a LUT. Value has been automatically set to 20 \n"); break;
    case 4:
    fprintf((stderr),"Missing/Unvalid option or name for output ppm file. Name has been automatically set to result.ppm \n"); break;
    case 5:
    fprintf((stderr),"PPM file saved successfully in folder ./images \n");break;
    case 6:
    fprintf((stderr),"Histogram saved successfully in folder ./images \n");break;
    default : 
    fprintf((stderr),"Unknown error\n");break;
  }
  
}

void displayExample(){
  fprintf((stderr), "Try something like : ./bin/minigimp PPM_IMAGE_NAME.ppm [-h] LUT_1 [VALUE_1] LUT_N [VALUE_N] [-o MYIMAGE.ppm] \n");
  fprintf((stderr), "Value parameter is unnecessary for : INVERT, SEPIA, RED, GREEN, BLUE and DAYTON \n");
}
