#include <iostream>
#include <raylib.h>
#include "globals.h"
Texture2D tiles;
Board board;

void LoadAssets(void)
{
	Image tmp = LoadImage("assets/Tiles.png");
	Image* bruh = &tmp;
        ImageResize(bruh, 48*3, 48*3);
	tiles = LoadTextureFromImage(tmp);
	//tiles = LoadTexture("assets/Tiles.png");
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
	Rectangle Destination;
	TextureBounds.height = 32;
	TextureBounds.width = 32;
	Destination.height = 32 * 1.5f;
	Destination.height = 32 * 1.5f;

	for (int i = 0; i < 7; ++i)
	{
		//DrawLineEx(Vector2{ board.bounds.x, board.bounds.y}, Vector2 { board.bounds.x+board.bounds.height, board.bounds.y/*+board.bounds.width*/}, 4.0f, BLACK);
		//DrawLineEx(Vector2{ board.bounds.x, board.bounds.y}, Vector2 { board.bounds.x/*+board.bounds.height*/, board.bounds.y+board.bounds.width}, 4.0f, BLACK);
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
			Destination.x = gridOffsetX + 4 + 32*i;
			Destination.y = gridOffsetY + 4 + 32*j;
			//DrawTextureTiled(tiles, TextureBounds, Destination, Vector2{TextureBounds.y+16, TextureBounds.x+16}, 0.0f, 1.5f, WHITE);
			//DrawTexturePro(tiles, TextureBounds, Destination, Vector2{TextureBounds.y, TextureBounds.x}, 0.0f, 1.5f, WHITE)
		}
	}

//	DrawRectangle(board.bounds, BLACK);
//			DrawTextureEx(Sprites, Vector2{GetScreenWidth()/2-Sprites.width, GetScreenHeight()/2-Sprites.width}, 0 , 2.0f, WHITE);
//	DrawTextureEx(Sprites, Vector2{GetMouseX(), GetMouseY()}, 0, 1.5f, WHITE);
//	DrawTextureEx(Sprites, Vector2{GetMouseX()+Sprites.height, GetMouseY()}, 0, 1.5f, WHITE);
//	DrawTextureEx(Sprites, Vector2{GetMouseX()+Sprites.height*2, GetMouseY()}, 0, 1.5f, WHITE);

}

int main(void)
{
//	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Geometry Slash");

	LoadAssets();

	SetTargetFPS(60);

	//for (int i = 0; i < 7; ++i)
	//{
	//	for (int j = 0; j < 7; ++j)
	//	{
	//		board.cells[i][j].color = static_cast<Colors>(GetRandomValue(0, 2));
	//		board.cells[i][j].shape = static_cast<Shapes>(GetRandomValue(0, 2));
	//	}
	//}

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update variables here

		BeginDrawing();

			DrawText("Bruh", 0, 0, 12, RED);
			DrawTexture(tiles, 0, 0, WHITE);
			//DrawBoard();
			ClearBackground(RAYWHITE);
			


		EndDrawing();
	}

	UnloadAssets();

	CloseWindow();
	return 0;
}
