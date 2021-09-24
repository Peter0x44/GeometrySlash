#ifndef NETWORK_H
#define NETWORK_H

#include <string>

void ReadURL(void);

void PostScores(void);
std::string& GetScores(const unsigned int page);

constexpr const char* PostSuffix = "/submit";
constexpr const char* GetSuffix = "/top?from=%u";

extern std::string ServerURL;

extern std::string GetEndpoint;
extern std::string PostEndpoint;

#endif
