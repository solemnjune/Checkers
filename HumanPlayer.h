#pragma once
#include "I_Player.h"

class HumanPlayer :
    public I_Player
{
public:
    HumanPlayer(Side playSide, GameFieldLogic* field): I_Player(playSide, field) {}
    bool selectSquare();
    ~HumanPlayer() {}
private:
};

