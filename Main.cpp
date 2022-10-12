#include <SDL.h>
#include <iostream>
#include "Interface_textures.h"
#include "Interface_functions.h"
#include "MainMenu.h"
#include "GameLoop.h"
#include "TwoPlayers.h"
#include <fstream>
#include <ctime>
#pragma warning(disable : 4996)




int main (int argc, char* argv[])
{

	std::ofstream logFile;
	logFile.open("ErrorLog.txt", std::ios_base::app);
	time_t timetoday;
	time(&timetoday);
	logFile << "Session Started at " << asctime(localtime(&timetoday));
	std::streambuf* oldrdbuf = std::cerr.rdbuf(logFile.rdbuf());

	//Start up SDL and create window
	if (!init())//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		std::cerr <<"Failed to initialize!\n";

	}
	//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
	SDL_RenderSetLogicalSize(gRenderer, 1920, 1080);
	
	SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	GameLoop game;
	game.Init();
	// check !init!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while (game.Running())
	{
		game.Update();
		game.Draw();
		game.HandleEvents();
	}

	logFile << "\nSession Ended\n\n";
	close();
	IMG_Quit();
	SDL_Quit();
	std::cerr.rdbuf(oldrdbuf);
	logFile.close();

	
	return 0;
}




