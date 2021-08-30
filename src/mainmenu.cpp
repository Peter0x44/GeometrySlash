#include <raylib.h>
#include "mainmenu.h"

void MainMenu::logic(void) 
{	
	//Determine size and position of Title Text
	TitleFontSize = GetScreenHeight()/10;
	TitleDims = MeasureTextEx(GetFontDefault(), "Geometry Slash " VERSION_NUMBER, TitleFontSize, TitleFontSize/10);
	TitlePos.x = GetScreenWidth()/2 - TitleDims.x/2;
	TitlePos.y = GetScreenHeight()/5 - TitleDims.y/2;

	//Determine size and position of Start button and text
	StartButton.width = (GetScreenWidth()/6)*4;
	StartButton.height = (GetScreenHeight()/4);
	StartButton.x = GetScreenWidth()/2 - StartButton.width/2;
	StartButton.y = (GetScreenHeight()/3)*2 - StartButton.height/2;
	StartDims = MeasureTextEx(GetFontDefault(), "Start", TitleFontSize, TitleFontSize/10);
	StartPos.x = GetScreenWidth()/2 - StartDims.x/2;
	StartPos.y = (GetScreenHeight()/3)*2 - StartDims.y/2;

	if (CheckCollisionPointRec(GetMousePosition(), StartButton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
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
	DrawRectangleRounded(StartButton, 0.5f, 0, LIGHTGRAY);
	DrawText("Start", StartPos.x, StartPos.y, TitleFontSize, BLACK);

	// Draw all shapes in scrolling line
	for (const scroller& bruh: q)
	{
		DrawTexturePro(tiles, bruh.source, bruh.dest, Vector2{0,0}, 0.0f, WHITE);
	}
} 
