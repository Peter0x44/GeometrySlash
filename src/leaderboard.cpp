#include <string>
#include <cmath>
#include <sstream>
#include <limits>
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
	else if (NextPageButton->clicked())
	{
		if (currentPage != pageCount) ++currentPage;
		if (currentPage == pageRequestWasMadeOn + 5) RequestScores(pageRequestWasMadeOn + 5);
	}
	else if (PrevPageButton->clicked())
	{
		if (currentPage > 0) --currentPage;
		if (currentPage < pageRequestWasMadeOn) RequestScores(pageRequestWasMadeOn - 5);
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
	DrawTextEx(Unifont, TextFormat("%d of %d",currentPage+1, pageCount+1), Vector2{Backboard.x, Backboard.y+Backboard.height}, GetScreenHeight()/30, 0, LIGHTGRAY);
	DrawRectangleRoundedLines(PlayerBackboard, 0.5f, 90.0f*16.0f, 5.0f, MAROON);
	const int positionWithinRequest = currentPage % 5 * scoresPerPage;
	int scorePos = 0;
	for (int i = positionWithinRequest; i < positionWithinRequest + scoresPerPage && i < usernames.size(); ++i) //Draw leaderboard scores
	{
		DrawTextEx( //Draw Rank
			Unifont,	
			TextFormat("%d", (pageRequestWasMadeOn)*scoresPerPage+i+1),
			{
				Vline1.x-(MeasureTextEx(Unifont, TextFormat("%d", (pageRequestWasMadeOn)*scoresPerPage+i+1), GetScreenHeight()/20, 0).x) - GetScreenWidth()/100,
				Vline1.y+((MeasureTextEx(Unifont, TextFormat("%d", (pageRequestWasMadeOn)*scoresPerPage+i+1), GetScreenHeight()/20, 0).y + GetScreenHeight()/55)*scorePos)
			},
			GetScreenHeight()/20,
			0,
			BLACK
		);
		DrawTextEx( //Draw Username
			Unifont,
			usernames[i].c_str(),
			{
				Vline2.x-(MeasureTextEx(Unifont, usernames[i].c_str(), GetScreenHeight()/20, 0).x) - GetScreenWidth()/100,
				Vline2.y+((MeasureTextEx(Unifont, usernames[i].c_str(), GetScreenHeight()/20, 0).y+ GetScreenHeight()/55)*scorePos)
			},
			GetScreenHeight()/20,
			0,
			BLACK
		);
		DrawTextEx( //Draw Score
			Unifont,
			scores[i].c_str(),
			{
				Backboard.x+Backboard.width-(MeasureTextEx(Unifont, scores[i].c_str(), GetScreenHeight()/20, 0).x) - GetScreenWidth()/100,
				Backboard.y+((MeasureTextEx(Unifont, scores[i].c_str(), GetScreenHeight()/20, 0).y+ GetScreenHeight()/55)*scorePos)
			},
			GetScreenHeight()/20,
			0,
			BLACK
		);
		++scorePos;
	}
	// Draw your last score
	DrawTextEx(
		Unifont,
	 	"You",
		{
			Vline1.x - MeasureTextEx(Unifont, "You", GetScreenHeight()/20, 0).x - GetScreenWidth()/100,
			PlayerBackboard.y + PlayerBackboard.height/2 - MeasureTextEx(Unifont, "You", GetScreenHeight()/20, 0).y/2
		},
		GetScreenHeight()/20,
		0,
		BLACK
	);
	DrawTextEx(
		Unifont,
	 	username,
		{
			Vline2.x-(MeasureTextEx(Unifont, username, GetScreenHeight()/20, 0).x) - GetScreenWidth()/100,
			PlayerBackboard.y + PlayerBackboard.height/2 - MeasureTextEx(Unifont, username, GetScreenHeight()/20, 0).y/2
		},
		GetScreenHeight()/20,
		0,
		BLACK
	);
	DrawTextEx(
		Unifont,
	 	TextFormat("%d", score),
		{
			PlayerBackboard.x + PlayerBackboard.width - (MeasureTextEx(Unifont, TextFormat("%d", score), GetScreenHeight()/20, 0).x) - GetScreenWidth()/100,
			PlayerBackboard.y + PlayerBackboard.height/2 - MeasureTextEx(Unifont, TextFormat("%d", score), GetScreenHeight()/20, 0).y/2
		},
		GetScreenHeight()/20,
		0,
		BLACK
	);
}

Leaderboard::Leaderboard(void)
{
	RequestScores(currentPage);

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

void Leaderboard::RequestScores(int page)
{
	pageRequestWasMadeOn = page;

	usernames.clear();
	scores.clear();
	csv.clear();

	// Parse leaderboard entries
	csv = GetScores(page);

	std::string buf;
	std::stringstream ss(csv);

	ss.ignore(std::numeric_limits<std::streamsize>::max(), ','); // discard "count," text
	std::getline(ss, buf, '\n'); // Read total number of scores

	try
	{
		// Convert from string to integer
		// Wrap in a try...catch block because std::stoi can throw an exception
		const int scoresCount = std::stoi(buf);
		// calculate total number of pages
		// there are 10 scores on each page
		pageCount = std::ceil(scoresCount / scoresPerPage);
	}
	catch (...)
	{
		// Well, rip converting to an integer failed
		// Probably the GET request did too.
		// There isn't really anything useful that can be done here
		// TODO either prevent state switching to begin with or go back to results screen
		pageCount = 0;
	}

	while(std::getline(ss, buf, ','))
	{
		usernames.push_back(buf);
		std::getline(ss, buf, '\n');
		scores.push_back(buf);
	}
}


Leaderboard::~Leaderboard(void)
{
	delete MainMenuButton;
	delete PlayAgainButton;
	delete BackButton;
	delete PrevPageButton;
	delete NextPageButton;
}
