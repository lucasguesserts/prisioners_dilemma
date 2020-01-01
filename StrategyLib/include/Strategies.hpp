#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <Strategy.hpp>
#include <Decision.hpp>

class AlwaysCooperate: public Strategy
{
	public:
		AlwaysCooperate(void)
			: Strategy(
					"Always Cooperate",
					"AllC",
					"Always cooperate."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class AlwaysDefect: public Strategy
{
	public:
		AlwaysDefect(void)
			: Strategy(
					"Always Defect",
					"AllD",
					"Always defect."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class TitForTat: public Strategy
{
	public:
		TitForTat(void)
			: Strategy(
					"Tit for Tat",
					"TFT",
					"Start cooperating. Copy opponent's last move afterwards."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

extern AlwaysCooperate allC;
extern AlwaysDefect    allD;
extern TitForTat       tft ;

#endif
