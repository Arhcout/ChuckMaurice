#include "ChuckMauriceau.h"
#include "Array.h"
#include <stddef.h>
#include <stdio.h>

int main(void){
  if(Init() == OK)
    Run();

  Quit();
  return 0;
}
