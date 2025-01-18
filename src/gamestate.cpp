#include "mainmenu.h"
#include "gamestate.h"
#include "ingame.h"
#include "resultsscreen.h"
#include "leaderboard.h"

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
			case GameStates::ResultsScreen:
				CurrentState = new ResultsScreen();
				break;
#ifdef SUPPORT_LEADERBOARD
			case GameStates::Leaderboard:
				CurrentState = new Leaderboard();
				break;
#endif
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

void SetNextState(const GameStates NewState)
{
	NextState = NewState;
}
