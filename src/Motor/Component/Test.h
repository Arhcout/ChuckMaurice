#pragma once
#include "../Entity.h"
#include "../Error.h"

struct TestComponent{
  fnUpdateComponent update;
  fnDestroyComponent destroy;
  int type;

  int value; 
};

enum Error InitTestCmp(struct TestComponent** out, int value);

