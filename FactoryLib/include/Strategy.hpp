#ifndef FACTORY_STRATEGY_HPP
#define FACTORY_STRATEGY_HPP

#include <memory>
#include <string>
#include "Decision.hpp"

namespace PrisonersDilemma
{

	struct StrategyInformation
	{
		const std::string name        = "";
		const std::string shortName   = "";
		const std::string description = "";
	};

	class Strategy
	: public StrategyInformation
	{
		public:
			Strategy(const StrategyInformation & fullInformation);
			virtual Decision makeInitialDecision(void) = 0;
			virtual Decision makeDecision(const Decision & partnerLastDecision) = 0;
	};

	using StrategyPtr = std::unique_ptr<Strategy>;

}

#endif
