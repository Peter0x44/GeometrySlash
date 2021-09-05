#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>

void PostScores(void);
char* GetScores(void);

constexpr const char* PostEndpoint = "http://localhost:3000/submit";
constexpr const char* GetEndpoint = "http://localhost:3000/top";

struct MemoryStruct
{
	char *memory;
	size_t size;
};

#endif
