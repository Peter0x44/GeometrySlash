#include <cmath>
#include <iostream>
#include <raylib.h>
#include "ingame.h"
#include "globals.h"

void InGame::logic(void)
{
	gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
	gridOffsetY = GetScreenHeight()/2 - gridHeight/2;
	// Calculate the position of the corner of the grid
	cursorX = GetMouseX();
	cursorY = GetMouseY();
	if (cursorX < gridOffsetX) // Cursor is outside of the grid
		cursorX = 0;
	else if (cursorX > gridOffsetX + gridHeight)
		cursorX = 6;
	else
		cursorX = (cursorX-gridOffsetX) / cellSize;
		// Use the formula mouseposition - grid corner position / cellsize to find the cell the cursor is on

	if (cursorY < gridOffsetY)
		cursorY = 0;
	else if (cursorY > gridOffsetY + gridHeight)
		cursorY = 6;
	else
		cursorY = (cursorY-gridOffsetY) / cellSize;
}

void InGame::render(void)
{
	DrawBoard();
}




void InGame::DrawBoard(void)
{
	board.bounds.x = gridOffsetX;
	board.bounds.y = gridOffsetY;
	board.bounds.height = gridHeight;
	board.bounds.width = gridWidth;
	DrawRectangleLinesEx(board.bounds, 4.0f, BLACK);
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
