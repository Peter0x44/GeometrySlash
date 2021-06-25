#ifndef INGAME_H
#define INGAME_H

#include "gamestate.h"

enum class Shapes
{
	Square,
	Circle,
	Triangle,
	Rhombus,
	Heart
};

enum class Colors
{
	Red,
	Yellow,
	Blue,
	Green,
	Orange
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

extern Texture2D tiles;


class InGame: public GameState
{
public:
	virtual void logic(void) override final;
	virtual void render(void) override final;
	virtual ~InGame(void) override final {};
	InGame(void);
private:
	void DrawBoard(void);
	Board board;
};

#endif
