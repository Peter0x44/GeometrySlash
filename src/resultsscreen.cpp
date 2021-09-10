#include <raylib.h>
#include <iostream>
#include <string>
#include "network.h"
#include "gamestate.h"
#include "resultsscreen.h"
#include "button.h"

void ResultsScreen::logic(void)
{
	//Determine size and position of GameOver Text
	GameOverFontSize = GetScreenHeight()/8;
	GameOverDims = MeasureTextEx(Unifont, "Game Over", GameOverFontSize, 0);
	GameOverPos.x = GetScreenWidth()/2 - GameOverDims.x/2;
	GameOverPos.y = GetScreenHeight()/10 - GameOverDims.y/2;

	//Determine size and position of Score Text
	ScoreFontSize = GetScreenHeight()/6;
	ScoreDims = MeasureTextEx(Unifont, TextFormat("%u", score), ScoreFontSize, 0);
	ScorePos.x = GetScreenWidth()/2 - ScoreDims.x/2;
	ScorePos.y = GetScreenHeight()/3 - ScoreDims.y/2;

	UsernameFontSize = GetScreenHeight()/14;

	MaxTextBoxDims = MeasureTextEx(Unifont, "MMMMMMMMMMMMMMMM", UsernameFontSize, 0);

	textBox.x = GetScreenWidth()/2 - MaxTextBoxDims.x/2 - 5;
	textBox.y = GetScreenHeight()/2 - MaxTextBoxDims.y/2 - 8;
	textBox.width = MaxTextBoxDims.x + 10;
	textBox.height = MaxTextBoxDims.y + 16;

	MainMenuButton->logic();
	PostScoreButton->logic();
	LeaderboardButton->logic();
	PlayAgainButton->logic();
	

	if (MainMenuButton->clicked())
	{
		SetNextState(GameStates::MainMenu);
	}
	else if (PlayAgainButton->clicked())
	{
		SetNextState(GameStates::InGame);
	}
	else if (LeaderboardButton->clicked())
	{
		SetNextState(GameStates::Leaderboard);
	}
	else if (PostScoreButton->clicked() && letterCount > 0)
	{
		PostScores();
	}


	// Code for Input box modified from Raylib example input box (https://github.com/raysan5/raylib/blob/master/examples/text/text_input_box.c)

	// Get char pressed (unicode character) on the queue
	int key = GetCharPressed();

	// Check if more characters have been pressed on the same frame
	while (key > 0)
	{
		// NOTE: Only allow keys in range [32..125]
		if ((key >= 32) && (key <= 125) && (letterCount < sizeof(username) - 1))
		{
			username[letterCount] = (char)key;
			username[letterCount+1] = '\0'; // Add null terminator at the end of the string.
			letterCount++;
		}

		key = GetCharPressed();  // Check next character in the queue
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		if (letterCount != 0) letterCount--;
		username[letterCount] = '\0';
	}

	framesCounter++;
}



void ResultsScreen::render(void)
{
	DrawTextEx(Unifont, "Game Over", GameOverPos, GameOverFontSize, 0, MAROON);
	DrawTextEx(Unifont, TextFormat("%d", score), ScorePos, ScoreFontSize, 0, BLACK);
	DrawRectangleRounded(textBox, 0.5f, 0, LIGHTGRAY);
	DrawRectangleRoundedLines(textBox, 0.5f, 0, 2.0f, MAROON);

	DrawTextEx(Unifont, username, Vector2{textBox.x + 5, textBox.y + 8}, UsernameFontSize, 0, MAROON);

	if (letterCount < sizeof(username) - 1)
	{
		// Draw blinking underscore char
		if (((framesCounter/30)%2) == 0) DrawTextEx(Unifont, "_", Vector2{textBox.x + 8 + MeasureTextEx(Unifont, username, UsernameFontSize, 0).x, textBox.y + 12}, UsernameFontSize, 0, MAROON);
	}

	MainMenuButton->draw();
	PostScoreButton->draw();
	LeaderboardButton->draw();
	PlayAgainButton->draw();
}

ResultsScreen::ResultsScreen(void)
{
	auto fontSizeCallback
	{
		[] (void)
		{
			return GetScreenHeight()/22.0f;
		}
	};

	// Button constructor takes a function that calculates the position of the rectangle
	MainMenuButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/3.0f)-(tmp.width/2.0f);
			tmp.y = (GetScreenHeight()/6.0f)*4-(tmp.height/2.0f);
			return tmp;
		},
		fontSizeCallback,
		"Main menu"
	);
	PostScoreButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/3.0f)-(tmp.width/2.0f);
			tmp.y = ((GetScreenHeight()/6.0f)*5.0f)-(tmp.height/2.0f);
			return tmp;
		},
		fontSizeCallback,
		"Submit score"
	);
	LeaderboardButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/3.0f)*2.0f-(tmp.width/2.0f);
			tmp.y = ((GetScreenHeight()/6.0f)*5.0f)-(tmp.height/2.0f);
			return tmp;
		},
		fontSizeCallback,
		"Leaderboard"
	);
	PlayAgainButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/3.0f)*2.0f-(tmp.width/2.0f);
			tmp.y = (GetScreenHeight()/6.0f)*4-(tmp.height/2.0f);
			return tmp;
		},
		fontSizeCallback,
		"Play again"
	);
}

ResultsScreen::~ResultsScreen(void)
{
	delete MainMenuButton;
	delete PostScoreButton;
	delete LeaderboardButton;
	delete PlayAgainButton;
}
