#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H
#include "gamestate.h"

class ResultsScreen: public GameState
{
private:

public:
	void logic(void) final override;
	void render(void) final override;
};

#endif
