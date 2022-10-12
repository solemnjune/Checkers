
#pragma once
#include "Interface_functions.h"
#include "I_GameStates.h"
#include "HoverMenuButton.h"


class MainMenu : public I_GameStates
{
public:
	MainMenu();
	~MainMenu();

	virtual bool Init(GameLoop* game);

	virtual void Draw();
	virtual void HandleEvents();
	virtual void Update();


private:
	void Render();

	wrapTexture menupng;
	GameLoop* gamePtr;

	HoverMenuButton TwoPlayersButton;
	HoverMenuButton vsCpuButton;
	HoverMenuButton optionsButton;
	HoverMenuButton exitButton;

	wrapTexture TwoPlayersTexture;
	wrapTexture vsCpuTexture;
	wrapTexture optionsTexture;
	wrapTexture exitTexture;


	SDL_Event event;
	int x, y;

	bool initButtonTextures();
};

