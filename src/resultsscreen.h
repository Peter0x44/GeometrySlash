#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H
#include <functional>
#include <cstring>
#include "globals.h"
#include "button.h"
#include "gamestate.h"

class ResultsScreen: public GameState
{
private:
	int letterCount = 0;
	
	int framesCounter = 0;

	//IMGUI Variables
	Vector2 GameOverDims;
	Vector2 GameOverPos;
	float GameOverFontSize;

	Vector2 ScoreDims;
	Vector2 ScorePos;
	float ScoreFontSize;

	float UsernameFontSize;
	Vector2 MaxTextBoxDims;
	Rectangle textBox;

	Button* MainMenuButton;
	Button* PostScoreButton;
	Button* LeaderboardButton;
	Button* PlayAgainButton;

public:
	void logic(void) final override;
	void render(void) final override;
	ResultsScreen(void);
	~ResultsScreen(void);
};

#endif
