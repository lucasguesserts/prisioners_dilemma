#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <Strategy.hpp>
#include <Decision.hpp>

class AlwaysCooperate: public Strategy
{
	public:
		const std::string name = "Always Cooperate";
		const std::string shortName = "AllC";
		const std::string description = "Always cooperate.";

		Decision makeDecision(
			[[maybe_unused]] std::vector<Decision> thisDecision,
			[[maybe_unused]] std::vector<Decision> partnerDecision) final
		{
			return Decision::cooperate;
		}
} alwaysCooperate;

#endif
