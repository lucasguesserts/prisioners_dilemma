#ifndef FACTORY_STRATEGIES_HPP
#define FACTORY_STRATEGIES_HPP

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
			AlwaysCooperate(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static std::function<std::unique_ptr<Strategy>(void)> creator(void);
	};

	class AlwaysDefect: public Strategy
	{
		public:
			AlwaysDefect(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static std::function<std::unique_ptr<Strategy>(void)> creator(void);
	};

	class TitForTat: public Strategy
	{
		public:
			TitForTat(void);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static std::function<std::unique_ptr<Strategy>(void)> creator(void);
	};

	class NaiveProber: public Strategy
	{
		public:
			NaiveProber(double probabilityOfDefecting = 0.10);
			Decision makeInitialDecision(void) final override;
			Decision makeDecision(const Decision & partnerLastDecision) final override;
			static std::function<std::unique_ptr<Strategy>(void)> creator(double probabilityOfDefecting);
		private:
			const double probabilityOfDefecting;
			bool decidedRandomlyToDefect(void) const;
	};

}

#endif
