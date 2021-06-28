#ifndef MAINMENU_H
#define MAINMENU_H
#include "gamestate.h"

class MainMenu: public GameState
{
private:
	Vector2 TitlePos;
	Vector2 TitleDims;
	Vector2 StartPos;
	Vector2 StartDims;
	int TitleFontSize;

	Rectangle StartButton;
	
public:
	
	void logic(void) final override;
	void render(void) final override;
};

#endif