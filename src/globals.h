#ifndef GLOBALS_H
#define GLOBALS_H

#include <array>
#include <raylib.h>

constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

constexpr int spriteSize = 48;
constexpr int paddingSize = 6;

constexpr int gridHeight = spriteSize*7 + paddingSize*8;
constexpr int gridWidth = spriteSize*7 + paddingSize*8;

constexpr int cellSize = spriteSize + paddingSize;

extern Texture2D tiles;

#endif
