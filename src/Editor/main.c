#include "ChuckMauriceau.h"

int main(void){
  if(CM_Init() == CM_OK)
    CM_Run();

  CM_Quit();
  return 0;
}
