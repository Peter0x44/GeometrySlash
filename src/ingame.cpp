#include <cmath>
#include <string.h>
#include <raylib.h>
#include "ingame.h"
#include "random.h"

void InGame::logic(void)
{
	// Logic for determining hovered tile
	if (IsWindowResized())
	{
		gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
		gridOffsetY = GetScreenHeight()/2 - gridHeight/2;
		// Calculate the position of the corner of the grid
	}
	cursorX = GetMouseX();
	cursorY = GetMouseY();
	if (cursorX < gridOffsetX) // Cursor is outside of the grid
		cursorX = 0;
	else if (cursorX > gridOffsetX + gridHeight - gridBorder*2)
		cursorX = 6;
	else
		cursorX = (cursorX-gridOffsetX) / cellSize;
		// Use the formula mouseposition - grid corner position / cellsize to find the cell the cursor is on

	if (cursorY < gridOffsetY)
		cursorY = 0;
	else if (cursorY > gridOffsetY + gridHeight - gridBorder*2)
		cursorY = 6;
	else
		cursorY = (cursorY-gridOffsetY) / cellSize;

	for (int i = 0; i < 7; ++i)
	{
		if (board.cells[i][0].color == Colors::Empty)
		{
			board.cells[i][0].color = static_cast<Colors>(GenerateRandomShapeOrColor());
			board.cells[i][0].shape = static_cast<Shapes>(GenerateRandomShapeOrColor());
		}
	}
	for (int j = 6; j >= 0; --j)
	{
		for (int i = 6; i >= 0; --i)
		{
			if (board.cells[i][j].color == Colors::Empty)
			{
				int jj = ((j - 1 < 0) ? 0 : j - 1 );
				while (jj >= 0)
				{
					if (board.cells[i][jj].color != Colors::Empty)
					{
						board.cells[i][jj+1].color = board.cells[i][jj].color;
						board.cells[i][jj+1].shape = board.cells[i][jj].shape;
						board.cells[i][jj].color = Colors::Empty;
						board.cells[i][jj].shape = Shapes::Empty;
					} else --jj;
				}
			}

		}
	}

	//Logic for chain selection
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if (Chain.empty())
		{
			Chain.push_back(bruh{cursorX, cursorY});
#ifndef GEKKO
			PlaySound(tones[0]);
#endif
		}
		else if (Chain.size() > 1)
		//if you hover over the second to last cell, pop it from the chain. Effectively, this allows going backwards.
		{
			if ((Chain.rbegin()[1].x == cursorX) && (Chain.rbegin()[1].y == cursorY))
			{
				Chain.pop_back();
#ifndef GEKKO
				PlaySound(tones[(Chain.size() -1) % 7]); //TODO: make more tones
#endif
			}
		}
		if (((std::abs(Chain.back().x  -  cursorX) <= 1) && (std::abs(Chain.back().y  -  cursorY) <= 1))
		&& ((cursorX == Chain.back().x) != (cursorY == Chain.back().y))) //only allow cardinal movements of ±1
		{
			bool found = false;
			for (const bruh& i: Chain)
			{
				if (i.x == cursorX && i.y == cursorY)
				{
					found = true;
				}
			}
			// Only add to chain if the X and Y coordinates are not already present
			if (!found && ((board.cells[Chain.back().x][Chain.back().y].color == board.cells[cursorX][cursorY].color) || (board.cells[Chain.back().x][Chain.back().y].shape == board.cells[cursorX][cursorY].shape)))
			// Only add to the chain if the color or shape is the same as the last in the chain
			{
				Chain.push_back(bruh{cursorX, cursorY});
#ifndef GEKKO
				PlaySound(tones[(Chain.size() - 1) % 7]); //TODO: make more tones
#endif
			}
		}
	}
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (Chain.size() == 1)
			Chain.clear();
		else
		{
			for (const bruh& i: Chain)
			{
				board.cells[i.x][i.y].color = Colors::Empty;
				board.cells[i.x][i.y].shape = Shapes::Empty;
			}
			scoreToAdd = Chain.size()*Chain.size();
			ScoreToAddPos = GetMousePosition();
			ScoreLifetime = 1.5f;
			ScoreToAddPos.x += 20 * GetFrameTime() * 60;
			ScoreToAddPos.y -= 20 * GetFrameTime() * 60;
			score += scoreToAdd;
			Chain.clear();
		}
	}
	//clear chain if mouse is released

	// Timer
	TimeLeft = gameLength - (GetTime() - startTime);
	if ((GetTime() - startTime) > gameLength)
	{
		SetNextState(GameStates::ResultsScreen);
	}
}

void InGame::render(void)
{
	if (!Chain.empty()) DrawChainLines();
	DrawBoard();
	DrawScore();
	DrawTimer();
	DrawScoreToAdd();
}


void InGame::DrawChainLines(void)
{
	for (size_t i = 0; i < Chain.size()-1; ++i)
	{
		Vector2 currentPoint = Vector2{ (float)Chain.at(i).x, (float)Chain.at(i).y };
		Vector2 nextPoint = Vector2{ (float)Chain.at(i+1).x+1, (float)Chain.at(i+1).y+1};
		currentPoint.x = gridOffsetX + (currentPoint.x * cellSize) + paddingSize + spriteSize/2;
		currentPoint.y = gridOffsetY + (currentPoint.y * cellSize) + paddingSize + spriteSize/2;
		nextPoint.x = gridOffsetX + ((nextPoint.x-1) * cellSize) + paddingSize + spriteSize/2;
		nextPoint.y = gridOffsetY + ((nextPoint.y-1) * cellSize) + paddingSize + spriteSize/2;

		DrawLineEx(currentPoint, nextPoint, 4.0f, BLACK);
	}
}



void InGame::DrawBoard(void)
{
	board.bounds.x = gridOffsetX;
	board.bounds.y = gridOffsetY;
	board.bounds.height = gridHeight;
	board.bounds.width = gridWidth;
	DrawRectangleLinesEx(board.bounds,(float)gridBorder, BLACK);
	Rectangle TextureBounds;
	TextureBounds.height = spriteSizeAtlas;
	TextureBounds.width = spriteSizeAtlas;
	Rectangle TileDest;
	TileDest.width = spriteSize;
	TileDest.height = spriteSize;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if (board.cells[i][j].color == Colors::Empty)
				continue;
			TextureBounds.x = spriteSizeAtlas * static_cast<int>(board.cells[i][j].color);
			TextureBounds.y = spriteSizeAtlas * static_cast<int>(board.cells[i][j].shape);
			// Enum values also correspond to position in texture atlas
			TileDest.x = gridOffsetX + paddingSize*(i+1) + spriteSize*i;
			TileDest.y = gridOffsetY + paddingSize*(j+1) + spriteSize*j;
			DrawTexturePro(tiles, TextureBounds, TileDest, Vector2{0,0}, 0.0f, WHITE);
		}
	}

}

void InGame::DrawScore(void)
{
	ScoreDims = MeasureTextEx(Unifont, TextFormat("Score: %u", score), ScoreFontSize, 0);
	ScorePos.x = GetScreenWidth()/2 - ScoreDims.x/2;
	ScorePos.y = gridOffsetY - ScoreDims.y;
	DrawTextEx(Unifont, TextFormat("Score: %u", score), ScorePos, ScoreFontSize, 0, RED);
}

void InGame::DrawScoreToAdd(void)
{
	// ScoreLifeTime determines how many seconds to show the score for
	if (ScoreLifetime > 0)
	{
		ScoreToAddColor = ColorAlpha(WHITE, ScoreLifetime/1.5f);
		DrawTextEx(Unifont, TextFormat("+%u", scoreToAdd), ScoreToAddPos, ScoreFontSize, 0, ScoreToAddColor);
		ScoreToAddPos.y -= 2 * GetFrameTime() * 60;
		ScoreLifetime -= GetFrameTime();
	}
}

void InGame::DrawTimer(void)
{
	TimerDims = MeasureTextEx(Unifont, TextFormat("Time: %d", TimeLeft), ScoreFontSize, 0);
	TimerPos.x = GetScreenWidth()/2 - TimerDims.x/2;
	TimerPos.y = (gridOffsetY*2) + gridHeight - TimerDims.y;
	DrawTextEx(Unifont, TextFormat("Time: %d", TimeLeft), TimerPos, ScoreFontSize, 0, BLUE);

}

InGame::InGame(void)
{
	score = 0;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			board.cells[i][j].color = static_cast<Colors>(GenerateRandomShapeOrColor());
			board.cells[i][j].shape = static_cast<Shapes>(GenerateRandomShapeOrColor());
		}
	}
	gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
	gridOffsetY = GetScreenHeight()/2 - gridHeight/2;
}
