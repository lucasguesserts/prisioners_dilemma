#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <string>

class Strategy
{
	public:
		std::string name = "";
		std::string description = "";
		unsigned numberOfMatches = 0u;
		unsigned accumulatedPayoff = 0u;
};

#endif
