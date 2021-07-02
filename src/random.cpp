#include <random>
#include <ctime>

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
// Seed with current time
std::uniform_int_distribution<> rng { 0, 4 };
// We only need to generate random values between 0 and 4

int GenerateRandomShapeOrColor(void)
{
	return rng(mersenne);
}
