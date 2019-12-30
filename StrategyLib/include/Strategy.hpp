#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <string>
#include <vector>
#include <Decision.hpp>

class Strategy
{
	public:
		const std::string name = "";
		const std::string description = "";
	
		virtual Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) = 0;
		virtual Decision initialDecision(void) = 0;
};

#endif
