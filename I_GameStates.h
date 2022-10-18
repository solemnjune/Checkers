#pragma once

class GameLoop;

class I_GameStates
{
public:

	virtual bool Init(GameLoop* game) = 0;

	virtual void Draw() = 0;
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;

	virtual ~I_GameStates() {}
};