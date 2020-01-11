#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <string>
#include <vector>
#include <Decision.hpp>

class Strategy
{
	public:
		std::string name;
		std::string shortName;
		std::string description;
	
		Strategy(void);
		Strategy(std::string name, std::string shortName, std::string description);
		virtual Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) = 0;
};

#endif
