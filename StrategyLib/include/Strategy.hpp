#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <string>
#include <vector>
#include <Decision.hpp>

class Strategy
{
	public:
		std::string name = "";
		std::string description = "";
		std::vector<unsigned> payoff;
	
		virtual Decision makeDecision(
			[[maybe_unused]] std::vector<Decision> thisDecision,
			[[maybe_unused]] std::vector<Decision> partnerDecision) = 0;
		virtual Decision initialDecision(void) = 0;
};

#endif
