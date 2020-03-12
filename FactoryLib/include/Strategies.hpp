#ifndef FACTORY_STRATEGIES_HPP
#define FACTORY_STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <functional>
#include "Strategy.hpp"
#include "Decision.hpp"

namespace PrisonersDilemma
{

	using StrategyCreator = std::function<StrategyPtr(void)>;

	class AlwaysCooperate: public Strategy
	{
		public:
			AlwaysCooperate(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static StrategyCreator creator(void);
	};

	class AlwaysDefect: public Strategy
	{
		public:
			AlwaysDefect(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static StrategyCreator creator(void);
	};

	class TitForTat: public Strategy
	{
		public:
			TitForTat(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static StrategyCreator creator(void);
	};

	class NaiveProber: public Strategy
	{
		public:
			NaiveProber(double probabilityOfDefecting = 0.10);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static StrategyCreator creator(double probabilityOfDefecting);
		private:
			const double probabilityOfDefecting;
			bool decidedRandomlyToDefect(void) const;
	};

}

#endif
