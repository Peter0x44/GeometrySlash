#include <cmath>
#include <iostream>
#include <raylib.h>
#include "ingame.h"
#include "globals.h"
#include "random.h"

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
			//std::cout << "i = " << i << " j = " << j << std::endl;
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

					} else jj--;
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
		}
		else if ((Chain.end()[-2].x == cursorX && Chain.end()[-2].y == cursorY) && (Chain.size() > 1)) 
		//if you hover over the second to last cell, pop it from the chain. Effectively, this allows going backwards.
		{
			Chain.pop_back();
		}
		else if (((std::abs(Chain.back().x  -  cursorX) <= 1) && (std::abs(Chain.back().y  -  cursorY) <= 1))
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
			Chain.clear();
		}
	}
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
			board.cells[i][j].color = static_cast<Colors>(GenerateRandomShapeOrColor());
			board.cells[i][j].shape = static_cast<Shapes>(GenerateRandomShapeOrColor());
		}
	}
}
