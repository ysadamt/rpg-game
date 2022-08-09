#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random
{
	static int getRandomNumber(int min, int max)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ min, max };

		return range(mt);
	}
}

#endif
