#include <raylib.h>
#include "mainmenu.h"

void MainMenu::logic(void) 
{	
	//Determine size and position of Title Text
	TitleFontSize = GetScreenHeight()/10;
	TitleDims = MeasureTextEx(GetFontDefault(), "Geometry Slash " VERSION_NUMBER, TitleFontSize, TitleFontSize/10);
	TitlePos.x = GetScreenWidth()/2 - TitleDims.x/2;
	TitlePos.y = GetScreenHeight()/5 - TitleDims.y/2;

	StartButton->logic();

	if (StartButton->clicked())
	{
		SetNextState(GameStates::InGame);
	}

	if (GetTime() > Timer)
	{
		// Add new shape to queue every spawnTime seconds. spawnTime is chosen so there is a gap of SpriteSize pixels between each one.
		scroller scroll;
		q.push_back(scroll);
		Timer += spawnTime;
	}

	if (!q.empty())
	{
		if (q.front().dest.x > GetScreenWidth())
		{
			q.pop_front();
			// Delete from queue if the front shape goes offscreen
		}
	}

	int y = GetScreenHeight()/3;

	for (scroller& scroller: q)
	{
		scroller.dest.x += scrollSpeed * GetFrameTime() * 60;
		// Move every shape by scrollSpeed pixels
		scroller.dest.y = y;
		// Set Y position of all of them, so it the positions stay correct when the window is resized
	}
}

void MainMenu::render(void)
{
	DrawText("Geometry Slash " VERSION_NUMBER, TitlePos.x, TitlePos.y, TitleFontSize, RED);

	StartButton->draw();

	// Draw all shapes in scrolling line
	for (const scroller& bruh: q)
	{
		DrawTexturePro(tiles, bruh.source, bruh.dest, Vector2{0,0}, 0.0f, WHITE);
	}
} 

MainMenu::MainMenu(void)
{
	StartButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = (GetScreenWidth()/6)*4;
			tmp.height = (GetScreenHeight()/4);
			tmp.x = GetScreenWidth()/2 - tmp.width/2;
			tmp.y = (GetScreenHeight()/3)*2 - tmp.height/2;
			return tmp;
		},
		[](void)
		{
			return GetScreenHeight()/10.0f;
		},
		"Start"
	);
}

MainMenu::~MainMenu(void)
{
	delete StartButton;
}
