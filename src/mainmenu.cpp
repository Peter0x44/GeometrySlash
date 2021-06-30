#include <raylib.h>
#include "mainmenu.h"

void MainMenu::logic(void) 
{	
	//Determine size and position of Title Text
	TitleFontSize = GetScreenHeight()/10;
	TitleDims = MeasureTextEx(GetFontDefault(), "Geometry Slash", TitleFontSize, TitleFontSize/10);
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

	static int frameCount;

	if (!(frameCount % (spriteSize*2 / scrollSpeed)))
	{
		// Add new shape to queue every sprite size * 2 frames (therefore leaving a gap of one sprite between them) and divide by speed modifier 
		scroller scroll;
		q.push_back(scroll);
	}

	if (q.front().dest.x > GetScreenWidth())
	{
		q.pop_front();
		// Delete from queue if the front shape goes offscreen
	}

	int y = GetScreenHeight()/3;

	for (scroller& scroller: q)
	{
		scroller.dest.x += scrollSpeed;
		// Move every shape by scrollSpeed pixels every frame
		scroller.dest.y = y;
		// Set Y position of all of them, so it the positions stay correct when the window is resized
	}

	++frameCount;
}

void MainMenu::render(void)
{
	ClearBackground(DARKGRAY);
	DrawText("Geometry Slash", TitlePos.x, TitlePos.y, TitleFontSize, RED);	
	DrawRectangleRounded(StartButton, 0.5f, 0, LIGHTGRAY);
	DrawText("Start", StartPos.x, StartPos.y, TitleFontSize, BLACK);

	// Draw all shapes in scrolling line
	for (const scroller& bruh: q)
	{
		DrawTexturePro(tiles, bruh.source, bruh.dest, Vector2{0,0}, 0.0f, WHITE);
	}
} 