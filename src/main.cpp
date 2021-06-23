#include <iostream>
#include <raylib.h>
#include "globals.h"
Texture2D tiles;
Board board;

void LoadAssets(void)
{
	tiles = LoadTexture("assets/Tiles.png");
}

void UnloadAssets(void)
{
	UnloadTexture(tiles);
}

void DrawBoard(void)
{
	board.bounds.x = gridOffsetX;
	board.bounds.y = gridOffsetY;
	board.bounds.height = gridHeight;
	board.bounds.width = gridWidth;
	DrawRectangleLinesEx(board.bounds, 4.0f, BLACK);
	Rectangle TextureBounds;
	TextureBounds.height = 32;
	TextureBounds.width = 32;
	Rectangle TileDest;
	TileDest.width = 48;
	TileDest.height = 48;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			switch (board.cells[i][j].color)
			{
				case Colors::Red:
					TextureBounds.x = 0;
					break;
				case Colors::Yellow:
					TextureBounds.x = 32;
					break;
				case Colors::Blue:
					TextureBounds.x = 64;
					break;
			}
			switch (board.cells[i][j].shape)
			{
				case Shapes::Square:
					TextureBounds.y = 0;
					break;
				case Shapes::Circle:
					TextureBounds.y = 32;
					break;
				case Shapes::Triangle:
					TextureBounds.y = 64;
					break;
			}
			TileDest.x = gridOffsetX + 6*(i+1) + 48*i;
			TileDest.y = gridOffsetY + 6*(j+1) + 48*j;
			DrawTexturePro(tiles, TextureBounds, TileDest, Vector2{0,0}, 0.0f, WHITE);
		}
	}



}

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Geometry Slash");

	LoadAssets();

	SetTargetFPS(60);

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			board.cells[i][j].color = static_cast<Colors>(GetRandomValue(0, 2));
			board.cells[i][j].shape = static_cast<Shapes>(GetRandomValue(0, 2));
		}
	}

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update variables here
		 gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
		 gridOffsetY = GetScreenHeight()/2 - gridHeight/2;
		BeginDrawing();

			DrawBoard();
			ClearBackground(RAYWHITE);


		EndDrawing();
	}

	UnloadAssets();

	CloseWindow();
	return 0;
}
