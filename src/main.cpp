#include <iostream>
#include <raylib.h>
#include "globals.h"
#include "gamestate.h"
#include "ingame.h"
#include "mainmenu.h"

Texture2D tiles;

GameState* CurrentState = nullptr;
GameStates StateID = GameStates::Null;
GameStates NextState = GameStates::Null;

long unsigned int score = 0;

void LoadAssets(void);
void UnloadAssets(void);

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Geometry Slash");
	SetTargetFPS(60);
	SetWindowMinSize(screenWidth, screenHeight);
	LoadAssets();

	CurrentState = new MainMenu();

	// Main game loop
	while (!WindowShouldClose())
	{
		CurrentState->logic();

		BeginDrawing();

			ClearBackground(Color{ 50, 50, 50, 255 });
			CurrentState->render();

		EndDrawing();

		ChangeState();
	}

	UnloadAssets();
	CloseWindow();

	return 0;
}

void LoadAssets(void)
{
	tiles = LoadTexture("assets/Tiles.png");
	SetTextureFilter(tiles, TEXTURE_FILTER_POINT);
}

void UnloadAssets(void)
{
	UnloadTexture(tiles);
}
