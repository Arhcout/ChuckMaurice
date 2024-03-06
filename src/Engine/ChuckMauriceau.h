#pragma once
#include "Error.h"

//Initialize the engine
enum Error Init();
//Starts the game loop
enum Error Run();
//Cleanup the engine
void Quit();
