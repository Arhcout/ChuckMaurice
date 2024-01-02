#pragma once
#include "Error.h"

//Initialize the engine
CM_Error CM_Init();
//Starts the game loop
CM_Error CM_Run();
//Cleanup the engine
void CM_Quit();
