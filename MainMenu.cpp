#include "MainMenu.h"
#include <iostream>
#include "GameLoop.h"


MainMenu::MainMenu() :TwoPlayersButton(HoverMenuButton::MenuChoice::twoPlayers, 4, 2, 4),
vsCpuButton(HoverMenuButton::MenuChoice::vsCPU, 4, 2, 4),
optionsButton(HoverMenuButton::MenuChoice::options, 4, 2, 4),
exitButton(HoverMenuButton::MenuChoice::exit, 4, 2, 4)
{
	HoverMenuButton::setSelectedButton() = HoverMenuButton::MenuChoice::twoPlayers;
}

MainMenu::~MainMenu()
{
	menupng.free();
}




bool MainMenu::Init(GameLoop* game)
{
	if (!menupng.loadFromFile("Menus/menu.png"))
	{
		std::cerr << "Failed to load media!\n";
		return false;
	}
	
	if (!initButtonTextures())
	{
		std::cerr << "Failed to load media for buttons!\n";
		return false;
	}
	
	gamePtr = game;

	TwoPlayersButton.init(&TwoPlayersTexture,96 , 356);
	vsCpuButton.init(&vsCpuTexture, 96, TwoPlayersButton.getYTrect() + 151);
	optionsButton.init(&optionsTexture, 96, vsCpuButton.getYTrect() + 151);
	exitButton.init(&exitTexture, 96, optionsButton.getYTrect() + 151);
	
	return true;

}

void MainMenu::Render()
{
	menupng.render(nullptr);
	TwoPlayersButton.render();
	vsCpuButton.render();
	optionsButton.render();
	exitButton.render();

}


void MainMenu::HandleEvents()
{
	int width, height;

	SDL_GetMouseState(&x, &y);
	if (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gamePtr->ExitGame();
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_q:
				gamePtr->ExitGame();

				break;
			case SDLK_s:
			case SDLK_DOWN:
				HoverMenuButton::changeSelectedButtonDown();
				break;
			case SDLK_w:
			case SDLK_UP:
				HoverMenuButton::changeSelectedButtonUp();
				break;
			case SDLK_RETURN:
				if (HoverMenuButton::getSelectedButton() == HoverMenuButton::MenuChoice::exit)
				{
					gamePtr->ExitGame();

				}
				else if (HoverMenuButton::getSelectedButton() == HoverMenuButton::MenuChoice::twoPlayers)
				{
					gamePtr->PushState(std::make_unique<TwoPlayers>());
				}
				break;

			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			SDL_GetWindowSize(gWindow, &width, &height);
			
			SDL_GetMouseState(&x, &y);
			x = (double)x * (double)((double)1920 / (double)width);
			y = (double)y * (double)((double)1080 / (double)height);

			if (TwoPlayersButton.mouseOnButton(x,y))
			{
				HoverMenuButton::setSelectedButton() = HoverMenuButton::MenuChoice::twoPlayers;
			}
			else if (vsCpuButton.mouseOnButton(x,y))
			{
				HoverMenuButton::setSelectedButton() = HoverMenuButton::MenuChoice::vsCPU;
			}
			else if (optionsButton.mouseOnButton(x,y))
			{
				HoverMenuButton::setSelectedButton() = HoverMenuButton::MenuChoice::options;
			}
			else if (exitButton.mouseOnButton(x,y))
			{
				HoverMenuButton::setSelectedButton() = HoverMenuButton::MenuChoice::exit;
			}


			break;
		case SDL_MOUSEBUTTONDOWN:
			
			SDL_GetWindowSize(gWindow, &width, &height);

			SDL_GetMouseState(&x, &y);
			x = (double)x * (double)((double)1920 / (double)width);
			y = (double)y * (double)((double)1080 / (double)height);
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (TwoPlayersButton.mouseOnButton(x, y))
				{
					gamePtr->PushState(std::make_unique<TwoPlayers>());
				}
				else if (exitButton.mouseOnButton(x, y))
				{
					gamePtr->ExitGame();
					break;
				}

			}
			break;

		default:
			break;
		}
	}
}

void MainMenu::Update()
{

}




void MainMenu::Draw()
{
	Render();
}


bool MainMenu::initButtonTextures()
{
    bool success = true;


    if (!TwoPlayersTexture.loadFromFile("menus/2players.png",true))
    {
        std::cerr << "failed to load media 2players.png!\n" << SDL_GetError() << std::endl;
		return false;
    }
    if (!vsCpuTexture.loadFromFile("menus/vscpu.png", true))
    {
        std::cerr << "failed to load media vscpu.png!\n" << SDL_GetError() << std::endl;
		return false;
    }
    if (!optionsTexture.loadFromFile("menus/options.png", true))
    {
        std::cerr << "failed to load media options.png!\n" << SDL_GetError() << std::endl;
		return false;
    }
    if (!exitTexture.loadFromFile("menus/exit.png", true))
    {
        std::cerr << "failed to load media exit.png!\n" << SDL_GetError() << std::endl;
		return false;
	}

    return true;
}