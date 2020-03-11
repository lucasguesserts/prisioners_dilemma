#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <cstddef>
#include <functional>
#include <vector>
#include <string>
#include "Strategy.hpp"
#include "Decision.hpp"

namespace PrisonersDilemma
{

	class AlwaysCooperate: public Strategy
	{
		public:
			AlwaysCooperate(void)
				: Strategy(
					{
						"Always Cooperate",
						"AllC",
						"Always cooperate."
					}) {}
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			// The method receives the same parameters as the constructor does.
			// It might be annoying to always define this function as receiving
			// the same parameters, capturing it and then giving it to 'make_unique'.
			static std::function<std::unique_ptr<Strategy>(void)> creator(void);
	};

}

#endif
