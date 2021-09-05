#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstddef>
#include <raylib.h>

#include "leaderboard.h"
#include "network.h"
#include "button.h"
#include "gamestate.h"

void Leaderboard::logic(void)
{	
	if (MainMenuButton->clicked())
	{
		SetNextState(GameStates::MainMenu);
	}
	else if (PlayAgainButton->clicked())
	{
		SetNextState(GameStates::InGame);
	}
	else if (BackButton->clicked())
	{
		SetNextState(GameStates::ResultsScreen);
	}
	
	MainMenuButton->logic();
	PlayAgainButton->logic();
	BackButton->logic();
	PrevPageButton->logic();
	NextPageButton->logic();

	Backboard = 
	{
		GetScreenWidth()/8.0f,
		GetScreenHeight()/40.0f,
		GetScreenWidth()/8.0f*6.0f,
		GetScreenHeight()/6.0f*4.0f
	};

	PlayerBackboard = 
	{	
		GetScreenWidth()/8.0f,
		(GetScreenHeight()/1.5f)+(GetScreenHeight()/15.0f),
		GetScreenWidth()/8.0f*6.0f,
		GetScreenHeight()/12.0f
	};

	//use the 4 elements of a Rectangle as start/end points and width of the line
	Vline1 = 
	{
		GetScreenWidth()/4.0f + GetScreenWidth()/40.0f, //startX
		GetScreenHeight()/40.0f, //startY
		0, //endX = startX since the line is vertical, so we don't need this at all
		GetScreenHeight()/1.25f //width, add to startY to get endY
	};

	Vline2 =
	{
		GetScreenWidth()/2.0f + GetScreenWidth()/10.0f + GetScreenWidth()/20.0f, //startX
		GetScreenHeight()/40.0f,
		0,
		GetScreenHeight()/1.25f
	};
	
}

void Leaderboard::render(void)
{
	MainMenuButton->draw();
	PlayAgainButton->draw();
	BackButton->draw();
	PrevPageButton->draw();
	NextPageButton->draw();
	DrawRectangleRounded(Backboard, 0.1f, 90.0f*16.0f, LIGHTGRAY);
	DrawRectangleRounded(PlayerBackboard, 0.5f, 90.0f*16.0f, LIGHTGRAY);
	DrawLineEx(Vector2{Vline1.x, Vline1.y}, Vector2{Vline1.x, Vline1.y+Vline1.height}, 4.0f, DARKGRAY);
	DrawLineEx(Vector2{Vline2.x, Vline2.y}, Vector2{Vline2.x, Vline2.y+Vline2.height}, 4.0f, DARKGRAY);
	DrawText("1 of 69420", Backboard.x, Backboard.y+Backboard.height, GetScreenHeight()/30, LIGHTGRAY);
	DrawRectangleRoundedLines(PlayerBackboard, 0.5f, 90.0f*16.0f, 5.0f, MAROON);
}

Leaderboard::Leaderboard(void)
{
	// Parse leaderboard entries
	csv = GetScores();

	std::string buf;
	std::stringstream ss(csv);

	std::vector<std::string> usernames;
	std::vector<uint32_t> scores;
	while(std::getline(ss, buf, ','))
	{
		usernames.push_back(buf);
		std::getline(ss, buf, '\n');
		scores.push_back(std::stoul(buf));
	}

	for (const std::string& bruh : usernames)
	{
		std::cout << bruh << std::endl;
	}
	for (const uint32_t& bruh : scores)
	{
		std::cout << bruh << std::endl;
	}

	// Instantiate UI buttons
	auto fontSizeCallback
	{
		[] (void)
		{
			return GetScreenHeight()/20.0f;
		}
	};

	MainMenuButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/6.0f)-(tmp.width/2.0f);
			tmp.y = (GetScreenHeight()/6.0f)*5;
			return tmp;
		},
		fontSizeCallback,
		"Main menu"
	);
	PlayAgainButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/6.0f)*3-(tmp.width/2.0f);
			tmp.y = (GetScreenHeight()/6.0f)*5;
			return tmp;
		},
		fontSizeCallback,
		"Play again"
	);
	BackButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/3.75f;
			tmp.height = GetScreenHeight()/7.5f;
			tmp.x = (GetScreenWidth()/6.0f)*5-(tmp.width/2.0f);
			tmp.y = (GetScreenHeight()/6.0f)*5;
			return tmp;
		},
		fontSizeCallback,
		"Back"
	);
	PrevPageButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/10.0f;
			tmp.height = GetScreenHeight()/10.0f;
			tmp.x = (GetScreenWidth()/10.0f)-(tmp.width)+GetScreenWidth()/80.0f;
			tmp.y = GetScreenHeight()/3;
			return tmp;
		},
		fontSizeCallback,
		"Prev"
	);
	NextPageButton = new Button (
		[](void)
		{
			Rectangle tmp;
			tmp.width = GetScreenWidth()/10.0f;
			tmp.height = GetScreenHeight()/10.0f;
			tmp.x = (GetScreenWidth())-(tmp.width)-GetScreenWidth()/80.0f;
			tmp.y = GetScreenHeight()/3;
			return tmp;
		},
		fontSizeCallback,
		"Next"
	);
	
}

Leaderboard::~Leaderboard(void)
{
	delete MainMenuButton;
	delete PlayAgainButton;
	delete BackButton;
	delete PrevPageButton;
	delete NextPageButton;
}
