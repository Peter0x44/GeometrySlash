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
Sound tones[7];

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
	InitAudioDevice();
	SetWindowState(FLAG_WINDOW_ALWAYS_RUN); 	
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

	tones[0] = LoadSound("assets/Tones/C3.wav");
	tones[1] = LoadSound("assets/Tones/D3.wav");
	tones[2] = LoadSound("assets/Tones/E3.wav");
	tones[3] = LoadSound("assets/Tones/F3.wav");
	tones[4] = LoadSound("assets/Tones/G3.wav");
	tones[5] = LoadSound("assets/Tones/A3.wav");
	tones[6] = LoadSound("assets/Tones/B3.wav");

#ifdef SUPPORT_LEADERBOARD
	CurlInit();
	ReadURL();
#endif
}

void UnloadAssets(void)
{
	UnloadImage(icon);
	UnloadTexture(tiles);
	UnloadFont(Unifont);

#ifdef SUPPORT_LEADERBOARD
	CurlCleanup();
#endif
}
