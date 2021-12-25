#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>
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

constexpr double spawnTime = (1.0/60.0) * spriteSize; // Determines how often to spawn a scrolling sprite.

constexpr int scrollSpeed = 2; //pixels per 60th of a second advance of scrolling sprites

constexpr double gameLength = 60.0;

extern uint32_t score;
extern char username[17];

extern Texture2D tiles;
extern Image icon;
extern Font Unifont;
extern Sound C3;
extern Sound D3;

#endif
