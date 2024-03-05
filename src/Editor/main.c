#include "ChuckMauriceau.h"
#include <stdio.h>

int main(void){
  if(Init() == OK)
    Run();

  Quit();
  return 0;
}
