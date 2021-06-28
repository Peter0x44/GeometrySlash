#include <raylib.h>
#include "mainmenu.h"

void MainMenu::logic(void) 
{	
	//Determine size and position of Title Text
	TitleFontSize = GetScreenHeight()/10;
	TitleDims = MeasureTextEx(GetFontDefault(), "Geometry Slash", TitleFontSize, TitleFontSize/10);
	TitlePos.x = GetScreenWidth()/2 - TitleDims.x/2;
	TitlePos.y = GetScreenHeight()/4 - TitleDims.y/2;

	//Determine size and position of Start button and text
	StartButton.width = (GetScreenWidth()/6)*4;
	StartButton.height = (GetScreenHeight()/4);
	StartButton.x = GetScreenWidth()/2 - StartButton.width/2;
	StartButton.y = (GetScreenHeight()/3)*2 - StartButton.height/2;
	StartDims = MeasureTextEx(GetFontDefault(), "Start", TitleFontSize, TitleFontSize/10);
	StartPos.x = GetScreenWidth()/2 - StartDims.x/2;
	StartPos.y = (GetScreenHeight()/3)*2 - StartDims.y/2;

	if (CheckCollisionPointRec(GetMousePosition(), StartButton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
		SetNextState(GameStates::InGame);
	}
}

void MainMenu::render(void)
{
	DrawText("Geometry Slash", TitlePos.x, TitlePos.y, TitleFontSize, RED);	
	DrawRectangleRounded(StartButton, 0.5f, 0, LIGHTGRAY);
	DrawText("Start", StartPos.x, StartPos.y, TitleFontSize, BLACK);
	
} 
