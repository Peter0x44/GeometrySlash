#include <cmath>
#include <iostream>
#include <raylib.h>
#include "ingame.h"
#include "globals.h"

void InGame::logic(void)
{
	// Logic for determining hovered tile
	gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
	gridOffsetY = GetScreenHeight()/2 - gridHeight/2;	
	// Calculate the position of the corner of the grid
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

	
	//Logic for chain selection
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if (Chain.empty())
		{
			Chain.push_back(bruh{cursorX, cursorY});
		}
		else if ((Chain.end()[-2].x == cursorX && Chain.end()[-2].y == cursorY) && (Chain.size() > 1)) 
		//if you hover over the second to last cell, pop it from the chain. Effectively, this allows going backwards.
		{
			Chain.pop_back();
		}
		else
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
			if (!found)
			{
				Chain.push_back(bruh{cursorX, cursorY});
			}
		}
	} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) Chain.clear();
	//clear chain if mouse is released

	int position = 0;
	for (const bruh& i: Chain)
	{
		std::cout << "Chain[" << position << "] .x: " << i.x << " .y:" << i.y << std::endl;
		++position;
	}
}

void InGame::render(void)
{
	DrawBoard();

	if (!Chain.empty())
	{
		DrawChainLines();
	}
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
			TextureBounds.x = spriteSizeAtlas * static_cast<int>(board.cells[i][j].color);
			TextureBounds.y = spriteSizeAtlas * static_cast<int>(board.cells[i][j].shape);
			// Enum values also correspond to position in texture atlas
			TileDest.x = gridOffsetX + paddingSize*(i+1) + spriteSize*i;
			TileDest.y = gridOffsetY + paddingSize*(j+1) + spriteSize*j;
			DrawTexturePro(tiles, TextureBounds, TileDest, Vector2{0,0}, 0.0f, WHITE);
		}
	}
}

InGame::InGame(void)
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			board.cells[i][j].color = static_cast<Colors>(GetRandomValue(0, 4));
			board.cells[i][j].shape = static_cast<Shapes>(GetRandomValue(0, 4));
		}
	}
}
