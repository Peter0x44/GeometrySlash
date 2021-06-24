#include <iostream>
#include <raylib.h>
#include "globals.h"
Texture2D tiles;
Board board;

void LoadAssets(void)
{
	tiles = LoadTexture("assets/Tiles.png");
	SetTextureFilter(tiles, TEXTURE_FILTER_POINT);
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
			TextureBounds.x = 32 * static_cast<int>(board.cells[i][j].color);
			TextureBounds.y = 32 * static_cast<int>(board.cells[i][j].shape);
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
			board.cells[i][j].color = static_cast<Colors>(GetRandomValue(0, 4));
			board.cells[i][j].shape = static_cast<Shapes>(GetRandomValue(0, 4));
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
