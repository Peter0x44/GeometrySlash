#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstddef>

#include "leaderboard.h"
#include "network.h"

void Leaderboard::logic(void)
{
}

void Leaderboard::render(void)
{
}

Leaderboard::Leaderboard(void)
{
	csv = GetScores();

	std::string buf;
	std::stringstream ss(csv);

	std::vector<std::string> usernames;
	std::vector<uint32_t> scores;
	while(std::getline(ss, buf, ','))
	{
		usernames.push_back(buf);
		std::getline(ss, buf, '\n');
		scores.push_back(std::stoul(buf));
	}

	for (const std::string& bruh : usernames)
	{
		std::cout << bruh << std::endl;
	}
	for (const uint32_t& bruh : scores)
	{
		std::cout << bruh << std::endl;
	}
}

Leaderboard::~Leaderboard(void)
{
}
