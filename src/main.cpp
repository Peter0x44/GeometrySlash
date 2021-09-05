#include <iostream>
#include <cstdint>
#include <raylib.h>
#include "globals.h"
#include "gamestate.h"
#include "ingame.h"
#include "mainmenu.h"
#include "leaderboard.h"

Texture2D tiles;
Image icon;

GameState* CurrentState = nullptr;
GameStates StateID = GameStates::Null;
GameStates NextState = GameStates::Null;

uint32_t score = 0;
char username[17] = "Username";

void LoadAssets(void);
void UnloadAssets(void);

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Geometry Slash");
	SetTargetFPS(60);
	SetWindowMinSize(screenWidth, screenHeight);
	LoadAssets();

	CurrentState = new Leaderboard();

	// Main game loop
	while (!WindowShouldClose())
	{
		CurrentState->logic();

		BeginDrawing();

			ClearBackground(DARKGRAY);
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
	icon = LoadImage("assets/Icon.png");
	SetWindowIcon(icon);

	tiles = LoadTexture("assets/Tiles.png");
	SetTextureFilter(tiles, TEXTURE_FILTER_POINT);
}

void UnloadAssets(void)
{
	UnloadImage(icon);
	UnloadTexture(tiles);
}
