#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H
#include <functional>
#include <cstring>
#include "button.h"
#include "gamestate.h"

class ResultsScreen: public GameState
{
private:
	char Username[17] = "Username"; 
	int letterCount = std::strlen(Username);
	
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

	float ButtonFontSize;


	Button* MainMenuButton;
//	Button PostScoreButton;
//	Button LeaderboardButton;
//	Button PlayAgainButton;


public:
	void logic(void) final override;
	void render(void) final override;
	ResultsScreen(void);
	~ResultsScreen(void);
};

#endif
