#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "globals.h"

enum class GameStates
{
	Null, // Used to indicate there is no state to change
	MainMenu,
	InGame
};

struct GameState
{
	virtual void logic(void) = 0;
	virtual void render(void) = 0;
	virtual ~GameState(){};
};

void ChangeState(void);

void SetNextState(GameStates NewState);

#endif
