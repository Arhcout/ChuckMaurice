#pragma once
#include "../Entity.h"
#include "../Error.h"

struct CM_TestComponent{
  fnUpdateComponent update;
  fnDestroyComponent destroy;
  int value; 
};

enum CM_Error CM_InitTestCmp(struct CM_TestComponent** out, int value);

