#ifndef GLOBALS_H
#define GLOBALS_H
#define VERSION_NUMBER "1.0b"

#include <array>
#include <raylib.h>

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

extern Texture2D tiles;

#endif
