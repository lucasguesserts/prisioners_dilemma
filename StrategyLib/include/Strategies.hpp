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

class RandomStrategy: public Strategy
{
	public:
		RandomStrategy(void)
			: Strategy(
					"Random Strategy",
					"RANDS",
					"Makes a random decision."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class GrimTrigger: public Strategy
{
	public:
		GrimTrigger(void)
			: Strategy(
					"Grim Trigger",
					"Grim",
					"Cooperates until the partner defects. Thereafter it defects."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

extern AlwaysCooperate allC;
extern AlwaysDefect    allD;
extern TitForTat       tft ;
extern RandomStrategy  randS;
extern GrimTrigger     grim;

#endif
