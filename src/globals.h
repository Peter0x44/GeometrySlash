#ifndef GLOBALS_H
#define GLOBALS_H

#include <array>
#include <raylib.h>

#define VERSION_NUMBER "v0.1b"

constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

constexpr int spriteSizeAtlas = 32;
constexpr int spriteSize = 48;
constexpr int paddingSize = 6;

constexpr int gridHeight = spriteSize*7 + paddingSize*8;
constexpr int gridWidth = spriteSize*7 + paddingSize*8;
constexpr int gridBorder = 4;

constexpr int cellSize = spriteSize + paddingSize;

constexpr int scrollSpeed = 2; //pixels per frame advance of scrolling sprites

constexpr double gameLength = 15.0;

extern long unsigned int score;

extern Texture2D tiles;

#endif
