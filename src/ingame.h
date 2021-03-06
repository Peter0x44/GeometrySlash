#ifndef INGAME_H
#define INGAME_H

#include <vector>
#include <array>

#include "gamestate.h"
#include "globals.h"

enum class Shapes
{
	Square,
	Circle,
	Triangle,
	Rhombus,
	Heart,
	Empty
};

enum class Colors
{
	Red,
	Yellow,
	Blue,
	Green,
	Orange,
	Empty
};


// Enum value also corresponds to position in texture atlas
// i.e atlas[2*cellsize][1*cellsize] == blue circle

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

struct bruh
{
	int x;
	int y;
};

class InGame: public GameState
{
public:
	virtual void logic(void) override final;
	virtual void render(void) override final;
	virtual ~InGame(void) override final {};
	InGame(void);
private:
	void DrawBoard(void);
	void DrawChainLines(void);
	void DrawScore(void);
	void DrawScoreToAdd(void);
	void DrawTimer(void);
	Board board;
	int cursorY, cursorX;
	int gridOffsetX;
	int gridOffsetY;
	int ScoreFontSize = 45;
	float ScoreLifetime = 0.0f;
	Color ScoreToAddColor;
	Vector2 ScoreDims;
	Vector2 ScorePos;
	Vector2 ScoreToAddPos;
	Vector2 TimerDims;
	Vector2 TimerPos;
	long unsigned int scoreToAdd = 0;
	std::vector<bruh> Chain;
	const double startTime = GetTime();
	int TimeLeft;
};

#endif
