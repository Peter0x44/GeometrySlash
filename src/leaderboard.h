#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>
#include <string>

#include "globals.h"
#include "gamestate.h"

class Leaderboard: public GameState
{
private:
	std::string csv;
public:
	void logic(void) final override;
	void render(void) final override;
	Leaderboard(void);
	~Leaderboard(void);
};

#endif
