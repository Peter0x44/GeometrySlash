#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>
#include <string>

#include "globals.h"
#include "gamestate.h"
#include "button.h"

static constexpr unsigned int scoresPerPage = 10;
static constexpr unsigned int pagesPerRequest = 5;

class Leaderboard: public GameState
{
private:
	std::string csv;
	std::vector<std::string> usernames;
	std::vector<std::string> scores;
	unsigned int pageCount = 0;
	unsigned int currentPage = 0;
	unsigned int pageRequestWasMadeOn = 0;

	//IMGUI Variables

	Button* MainMenuButton;
	Button* PlayAgainButton;
	Button* BackButton;
	Button* PrevPageButton;
	Button* NextPageButton;
	Rectangle Backboard;
	Rectangle PlayerBackboard;
	Rectangle Vline1;
	Rectangle Vline2;

public:
	void RequestScores(unsigned int page);
	void logic(void) final override;
	void render(void) final override;
	Leaderboard(void);
	~Leaderboard(void);
};

#endif
