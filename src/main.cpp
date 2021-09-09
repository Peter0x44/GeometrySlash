#include <iostream>
#include <cstdint>
#include <raylib.h>
#include "globals.h"
#include "gamestate.h"
#include "ingame.h"
#include "mainmenu.h"
#include "leaderboard.h"

#define DEBUG_MENU 0

Texture2D tiles;
Image icon;
Font Unifont;

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

	CurrentState = new MainMenu();

	// Main game loop
	while (!WindowShouldClose())
	{
		if(DEBUG_MENU && IsKeyDown(KEY_TAB)) {
			switch (GetKeyPressed())
			{
			case KEY_ONE:
				SetNextState(GameStates::MainMenu);
				break;
			case KEY_TWO:
				SetNextState(GameStates::InGame);
				break;
			case KEY_THREE:
				SetNextState(GameStates::ResultsScreen);
				break;
			case KEY_FOUR:
				SetNextState(GameStates::Leaderboard);
				break;
			default:
				break;
			}
		}

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

	Unifont = LoadFont("assets/Unifont.ttf");
}

void UnloadAssets(void)
{
	UnloadImage(icon);
	UnloadTexture(tiles);
	UnloadFont(Unifont);
}
