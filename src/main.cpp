#include <raylib.h>
#include "globals.h"

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Geometry Slash");

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update

		BeginDrawing();

			ClearBackground(RAYWHITE);

			DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
