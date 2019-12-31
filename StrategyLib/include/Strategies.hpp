#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

#include <Strategy.hpp>
#include <Decision.hpp>

class AlwaysCooperate: public Strategy
{
	public:
		Decision makeDecision(
			[[maybe_unused]] std::vector<Decision> thisDecision,
			[[maybe_unused]] std::vector<Decision> partnerDecision) final
		{
			return Decision::cooperate;
		}
} alwaysCooperate;

#endif
