#pragma once
#include "Interface_textures.h"
//#include "Interface_MenuButton.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(wrapTexture& wT, std::string path);



//Frees media and shuts down SDL
void close();