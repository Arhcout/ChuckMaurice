#pragma once
#include "Error.h"

//Initialize the engine
enum CM_Error CM_Init();
//Starts the game loop
enum CM_Error CM_Run();
//Cleanup the engine
void CM_Quit();
