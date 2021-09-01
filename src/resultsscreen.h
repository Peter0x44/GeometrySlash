#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H
#include "gamestate.h"

class ResultsScreen: public GameState
{
private:
	char Username[17] = "Username"; 
	int letterCount = strlen(Username);
	
	int framesCounter;

	//IMGUI Variables
	Vector2 TitleDims;
	Vector2 TitlePos;
	float TitleFontSize;

	Vector2 ScoreDims;
	Vector2 ScorePos;
	float ScoreFontSize;

	float UsernameFontSize;
	Vector2 MaxTextBoxDims;
	Rectangle textBox;


public:
	void logic(void) final override;
	void render(void) final override;
};

#endif
