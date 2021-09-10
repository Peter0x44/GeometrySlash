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

void CurlInit(void);
void CurlCleanup(void);
void ReadURL(void);
// Implementation of these functions lies in network.cpp
// Didn't feel like exposing them because it just wasn't necessary

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, "Geometry Slash");
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

	CurlInit();
	ReadURL();
}

void UnloadAssets(void)
{
	UnloadImage(icon);
	UnloadTexture(tiles);
	UnloadFont(Unifont);

	CurlCleanup();
}
