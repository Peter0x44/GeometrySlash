#include "mainmenu.h"
#include "gamestate.h"
#include "ingame.h"

extern GameState* CurrentState;
extern GameStates StateID;
extern GameStates NextState;

void ChangeState(void)
{
	if (NextState != GameStates::Null)
	{
		delete CurrentState;

		switch (NextState)
		{
			case GameStates::MainMenu:
				CurrentState = new MainMenu();
				break;
			case GameStates::InGame:
				CurrentState = new InGame();
				break;
			case GameStates::Null:
				break;
				// Should never happen, but lets kill the stupid warning anyway
		}
		// Change the current game state
		StateID = NextState;

		// Set the next state to Null
		NextState = GameStates::Null;
	}
}

void SetNextState(GameStates NewState)
{
	NextState = NewState;
}
