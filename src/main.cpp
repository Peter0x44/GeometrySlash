#include <raylib.h>
#include "globals.h"

Texture2D Sprites;

void LoadAssets(void)
{
	Sprites = LoadTexture("../assets/Geometry_Slash_Sprites.png");
}

void UnloadAssets(void)
{
	UnloadTexture(Sprites);
}

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Geometry Slash");

	LoadAssets();

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update

		BeginDrawing();

			ClearBackground(RAYWHITE);
			DrawTexture(Sprites, 0, 0, WHITE);

		EndDrawing();
	}

	UnloadAssets();

	CloseWindow();
	return 0;
}
