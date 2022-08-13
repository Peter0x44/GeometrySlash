#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "globals.h"

enum class GameStates
{
	Null, // Used to indicate there is no state to change
	MainMenu,
	InGame,
	ResultsScreen,
	Leaderboard
};

struct GameState
{
	virtual void logic(void) = 0;
	virtual void render(void) = 0;

	GameState(void) = default;
	GameState(const GameState&) = delete; // no copy constructor
	GameState& operator=(const GameState&) = delete; // no assignment operator

	virtual ~GameState(){};

};

void ChangeState(void);

void SetNextState(const GameStates NewState);

#endif
