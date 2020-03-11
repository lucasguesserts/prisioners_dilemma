#ifndef FACTORY_STRATEGY_HPP
#define FACTORY_STRATEGY_HPP

#include <memory>
#include <string>
#include <vector>
#include "Decision.hpp"

namespace PrisonersDilemma
{

	struct StrategyDescription
	{
		const std::string name;
		const std::string shortName;
		const std::string description;
		StrategyDescription(
			const std::string & name,
			const std::string & shortName,
			const std::string & description);
	};

	class Strategy
	: public StrategyDescription
	{
		public:
			Strategy(const StrategyDescription & fullDescription);
			virtual Decision makeInitialDecision(void) = 0;
			virtual Decision makeDecision(const Decision & partnerLastDecision) = 0;
	};

}

#endif
