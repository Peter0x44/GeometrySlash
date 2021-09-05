#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>
#include <string>

void PostScores(void);
std::string& GetScores(void);

constexpr const char* PostEndpoint = "http://localhost:3000/submit";
constexpr const char* GetEndpoint = "http://localhost:3000/top";

struct MemoryStruct
{
	char *memory;
	size_t size;
};

#endif
