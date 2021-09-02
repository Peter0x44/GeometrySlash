#ifndef MAINMENU_H
#define MAINMENU_H
#include <raylib.h>
#include <deque>
#include "globals.h"
#include "button.h"
#include "gamestate.h"

struct scroller
{
	Rectangle dest;
	Rectangle source;
	scroller(void)
	{
		dest.x = -spriteSize;
		source.x = GetRandomValue(0, 4) * spriteSizeAtlas;
		source.y = GetRandomValue(0, 4) * spriteSizeAtlas;
		source.height = source.width = spriteSizeAtlas;
		dest.height = dest.width = spriteSize;
	}
};

class MainMenu: public GameState
{
private:
	std::deque<scroller> q;
	Vector2 TitlePos;
	Vector2 TitleDims;
	Button* StartButton;
	int TitleFontSize;
	double Timer = GetTime() + spawnTime; // Timer that determines how often to spawn a scrolling sprite
public:
	void logic(void) final override;
	void render(void) final override;
	MainMenu(void);
	~MainMenu(void);
};

#endif
