#ifndef GLOBALS_H
#define GLOBALS_H

#include <array>

constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

constexpr int gridHeight = 48*7 + 6*8;
constexpr int gridWidth = 48*7 + 6*8;

int gridOffsetX = GetScreenWidth()/2 - gridWidth/2;
int gridOffsetY = GetScreenHeight()/2 - gridHeight/2;

enum class Shapes
{
	Square,
	Circle,
	Triangle
};

enum class Colors
{
	Red,
	Yellow,
	Blue
};


// Enum value also corresponds to position in texture atlas
// i.e atlas[2][1] == blue circle

struct Tile
{
	Colors color;
	Shapes shape;
};

struct Board
{
	Rectangle bounds;
	std::array<std::array<Tile, 7>, 7> cells;
};

extern Board board;

extern Texture2D tiles;

#endif
