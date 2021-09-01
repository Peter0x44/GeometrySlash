#include <raylib.h>
#include "resultsscreen.h"
#include "button.h"

void ResultsScreen::logic(void)
{
	//Determine size and position of GameOver Text
	GameOverFontSize = GetScreenHeight()/8;
	GameOverDims = MeasureTextEx(GetFontDefault(), "Game Over", GameOverFontSize, GameOverFontSize/10);
	GameOverPos.x = GetScreenWidth()/2 - GameOverDims.x/2;
	GameOverPos.y = GetScreenHeight()/10 - GameOverDims.y/2;

	//Determine size and position of Score Text
	ScoreFontSize = GetScreenHeight()/6;
	ScoreDims = MeasureTextEx(GetFontDefault(), TextFormat("%d", score), ScoreFontSize, ScoreFontSize/10);
	ScorePos.x = GetScreenWidth()/2 - ScoreDims.x/2;
	ScorePos.y = GetScreenHeight()/3 - ScoreDims.y/2;

	UsernameFontSize = GetScreenHeight()/14;

	MaxTextBoxDims = MeasureTextEx(GetFontDefault(), "MMMMMMMMMMMMMMMM", UsernameFontSize, UsernameFontSize/10);

	textBox.x = GetScreenWidth()/2 - MaxTextBoxDims.x/2 - 5;
	textBox.y = GetScreenHeight()/2 - MaxTextBoxDims.y/2 - 8;
	textBox.width = MaxTextBoxDims.x + 10;
	textBox.height = MaxTextBoxDims.y + 16;
	
	// Code for Input box modified from Raylib example input box (https://github.com/raysan5/raylib/blob/master/examples/text/text_input_box.c)

	// Get char pressed (unicode character) on the queue
	int key = GetCharPressed();

	// Check if more characters have been pressed on the same frame
	while (key > 0)
	{
		// NOTE: Only allow keys in range [32..125]
		if ((key >= 32) && (key <= 125) && (letterCount < sizeof(Username) - 1))
		{
			Username[letterCount] = (char)key;
			Username[letterCount+1] = '\0'; // Add null terminator at the end of the string.
			letterCount++;
		}

		key = GetCharPressed();  // Check next character in the queue
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		letterCount--;
		if (letterCount < 0) letterCount = 0;
		Username[letterCount] = '\0';
	}

	framesCounter++;

////////MainMenuButtonRect.width = PostScoreButtonRect.width = LeaderboardButtonRect.width = PlayAgainButtonRect.width = GetScreenWidth()/4.0f;
////////MainMenuButtonRect.height = PostScoreButtonRect.height = LeaderboardButtonRect.height = PlayAgainButtonRect.height = GetScreenHeight()/7.5f;

////////MainMenuButtonRect.x = PostScoreButtonRect.x = (GetScreenWidth()/3.0f)-(MainMenuButtonRect.width/2.0f);
////////LeaderboardButtonRect.x = PlayAgainButtonRect.x = (GetScreenWidth()/3.0f)*2.0f-(MainMenuButtonRect.width/2.0f);

////////MainMenuButtonRect.y = PlayAgainButtonRect.y = (GetScreenHeight()/6.0f)*4-(MainMenuButtonRect.height/2.0f);
////////LeaderboardButtonRect.y = PostScoreButtonRect.y = ((GetScreenHeight()/6.0f)*5.0f)-(MainMenuButtonRect.height/2.0f);


}

Rectangle MainMenuButtonRectCallback(void)
{
        Rectangle tmp;
        tmp.width = GetScreenWidth()/4.0f;
        tmp.height = GetScreenHeight()/7.5f;
        tmp.x = (GetScreenWidth()/3.0f)-(tmp.width/2.0f);
        tmp.y = (GetScreenHeight()/6.0f)*4-(tmp.height/2.0f);
        return tmp;
}


void ResultsScreen::render(void)
{
	DrawText("Game Over", GameOverPos.x, GameOverPos.y, GameOverFontSize, MAROON);
	DrawText(TextFormat("%d", score), ScorePos.x, ScorePos.y, ScoreFontSize, BLACK);
	DrawRectangleRounded(textBox, 0.5f, 0, LIGHTGRAY);
	DrawRectangleRoundedLines(textBox, 0.5f, 0, 2.0f, MAROON);

	DrawText(Username, textBox.x + 5, textBox.y + 8, UsernameFontSize, MAROON);

	if (letterCount < sizeof(Username) - 1)
	{
		// Draw blinking underscore char
		if (((framesCounter/30)%2) == 0) DrawText("_", textBox.x + 8 + MeasureText(Username, UsernameFontSize), textBox.y + 12, UsernameFontSize, MAROON);
	}
	MainMenuButton->draw();
////////DrawRectangleRec(MainMenuButtonRect, LIGHTGRAY);
////////DrawRectangleRec(PostScoreButtonRect, LIGHTGRAY);
////////DrawRectangleRec(LeaderboardButtonRect, LIGHTGRAY);
////////DrawRectangleRec(PlayAgainButtonRect, LIGHTGRAY);
}


ResultsScreen::ResultsScreen(void)
{
	MainMenuButton = new Button(&MainMenuButtonRectCallback);
}
