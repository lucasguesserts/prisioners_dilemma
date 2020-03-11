#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <memory>
#include <string>
#include <vector>
#include "Decision.hpp"

namespace PrisonersDilemma
{

	class Strategy
	{
		public:
			const std::string name;
			const std::string shortName;
			const std::string description;
		
			Strategy(void);
			Strategy(const std::string& name, const std::string& shortName, const std::string& description);
			virtual Decision makeDecision(
				const std::vector<Decision>& thisDecision,
				const std::vector<Decision>& partnerDecision) const = 0;
	};

}

#endif
