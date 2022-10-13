
#include "TwoPlayers.h"
#include "Interface_functions.h"
#include <iostream>
#include "GameLoop.h"
#include "VictoryStateMini.h"
TwoPlayers::TwoPlayers(): endTurnButton(3,3,3), surrenderButton (3,3,3), blackDrawButton (5,2,6), whiteDrawButton (5,2,6)
{

}


TwoPlayers::~TwoPlayers()
{
	gameScreen.free();

}


bool TwoPlayers::Init(GameLoop* game)
{
	if (!(loadMedia(gameScreen,"PlayingGame/GameScreen.png")
		&& checkersPiecesMiniTexture.loadFromFile("PlayingGame/CheckersSmall.png", true)
		&& buttonsTexture.loadFromFile("PlayingGame/Buttons.png", true)
		&& numbersTexture.loadFromFile("PlayingGame/Numbers.png", true)))
	{
		std::cerr << "Failed to load media!\n";
		return false;
	}
	else
	{
		
		if (!field.init())
		{
			return false;
		}
	}
	gamePtr = game;

	endTurnButton.init(&buttonsTexture, 1070, 940, buttonsTexture.getOriginalWidth() / 2, buttonsTexture.getOriginalWidth() / 4 );
	surrenderButton.init(&buttonsTexture, 1640, 940, buttonsTexture.getOriginalWidth() / 4*3, buttonsTexture.getOriginalWidth() / 4);
	whiteDrawButton.init(&buttonsTexture, 1500, 655, 0, buttonsTexture.getOriginalWidth() / 2);
	blackDrawButton.init(&buttonsTexture, 1500, 255, 0, buttonsTexture.getOriginalWidth() / 2);

	checkersPiecesMiniTexture.setHeigth(checkersPiecesMiniTexture.getOriginalHeight() / 2);
	numbersTexture.setWidth(numbersTexture.getOriginalWidth() / 13);
	numbersTexture.setHeigth(numbersTexture.getOriginalHeight() / 2);

	whitePlayer = std::make_unique<HumanPlayer>(PlayerSide::white, &field);
	blackPlayer = std::make_unique<HumanPlayer>(PlayerSide::black, &field);
	whitePlayer->NullifyWinsAndCounts();
	blackPlayer->NullifyWinsAndCounts(); 

	whitePlayer->setMiniCheckers(&checkersPiecesMiniTexture, 1280, 740);
	blackPlayer->setMiniCheckers(&checkersPiecesMiniTexture, 1280, 340);
	whitePlayer->setNumbers(&numbersTexture, 1500, 500);
	blackPlayer->setNumbers(&numbersTexture, 1600, 500);
	whitePlayer->setArrow(&buttonsTexture, 1157, 655);
	blackPlayer->setArrow(&buttonsTexture, 1157, 255);

	currentSidep = &whitePlayer;

	victoryScreenShown = false;


	return true;
}




void TwoPlayers::HandleEvents()
{
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

			case SDLK_ESCAPE:
				gamePtr->PopState();
				break;
			default:
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			
			int width, height;
			SDL_GetWindowSize(gWindow, &width, &height);

			SDL_GetMouseState(&x, &y);
			x = (double)x * (double)((double)SCREEN_WIDTH / (double)width);
			y = (double)y * (double)((double)SCREEN_HEIGHT / (double)height);
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (field.mouseOnField(x,y))
				{
					field.handleEvents(x,y);
				}
				else if (endTurnButton.mouseOnButton(x, y))
				{
					if (field.getKillMode())
					{
						endTurnButton.pressButton();
						field.nullifyKillMode();
						changeTurnSide();
					}
				}
				else if (surrenderButton.mouseOnButton(x, y))
				{
					surrenderButton.pressButton();
					makeNewGame();
				}
				else if (whiteDrawButton.mouseOnButton(x, y) && currentSidep == &whitePlayer)
				{
					whiteDrawButton.pressButton();
					
				}
				else if (blackDrawButton.mouseOnButton(x, y) && currentSidep == &blackPlayer)
				{
					blackDrawButton.pressButton();
				}
				else
				{
					field.nullifySpecialSquares();
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				field.nullifySpecialSquares();
			}
			break;


		default:
			break;
		}




	}
}



void TwoPlayers::Update()
{
	if (victoryScreenShown)
	{
		blackPlayer->setCheckersKilled() = 0;
		whitePlayer->setCheckersKilled() = 0;
		currentSidep = &whitePlayer;
		field.makeNewGame();
		victoryScreenShown = false;
	}
	if (field.update(*currentSidep))
	{
		changeTurnSide();
	}
	if (whiteDrawButton.isMaxStage() && blackDrawButton.isMaxStage())
	{
		whiteDrawButton.nullifyButton();
		blackDrawButton.nullifyButton();
		makeNewGame(true);
	}
}




void TwoPlayers::Draw()
{
	


	
	gameScreen.render( nullptr);
	field.render();

	blackPlayer->render();
	whitePlayer->render();
	currentSidep->get()->renderArrow();

	if (field.getKillMode())
	{
		endTurnButton.render();
	}
	surrenderButton.render();
	whiteDrawButton.render();
	blackDrawButton.render();

}

void TwoPlayers::changeTurnSide()
{
	if (currentSidep == &whitePlayer)
	{

		currentSidep = &blackPlayer;
	}
	else
	{

		currentSidep = &whitePlayer;
	}
	if (!field.checkAbilityToMove(*currentSidep))
	{
		makeNewGame();
	}
	else
	{
		field.checkMandatoryMoves(*currentSidep);
	}
	endTurnButton.nullifyButton();
}
void  TwoPlayers::updateCheckersOwned()
{
	if (currentSidep == &whitePlayer)
	{
		blackPlayer->setCheckersKilled()--;
	}
	else
	{
		whitePlayer->setCheckersKilled()--;
	}
}

void TwoPlayers::makeNewGame(bool draw)
{
	if (draw == 0)
	{
		if (currentSidep == &whitePlayer)
		{
			lastWinner = Winner::Black;
			gamePtr->PushState(std::make_unique<VictoryStateMini>(static_cast<int>(lastWinner)));
			if (++blackPlayer->setWins() > 12)
			{
				blackPlayer->setWins() = 0;
				whitePlayer->setWins() = 0;
			}
		}
		else
		{
			lastWinner = Winner::White;
			gamePtr->PushState(std::make_unique<VictoryStateMini>(static_cast<int>(lastWinner)));
			if (++whitePlayer->setWins() > 12)
			{
				blackPlayer->setWins() = 0;
				whitePlayer->setWins() = 0;
			}
		}
	} 
	else
	{
		lastWinner = Winner::Draw;
		gamePtr->PushState(std::make_unique<VictoryStateMini>(static_cast<int>(lastWinner)));
	}
	victoryScreenShown = true;
}