#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <vector>
#include <tuple>
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

class Pavlov: public Strategy
{
	public:
		Pavlov(void)
			: Strategy(
					"Pavlov",
					"PVL",
					"Start cooperating. Repeat decision if a reward or temptation is received. Change last decision otherwise (if sucker's or punishment is received)."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class TitForTwoTats: public Strategy
{
	public:
		TitForTwoTats(void)
			: Strategy(
					"Tit for Two Tats",
					"TFTT",
					"Start cooperating. defects when the partner defects twice in a row."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class GradualS: public Strategy
{
	public:
		GradualS(void)
			: Strategy(
					"Gradual Strategy",
					"GradualS",
					"Start cooperating. When the partner defects, it defects as many times as the partner has defected and then cooperates twice."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
		// Auxiliar
		static std::vector<std::tuple<unsigned,unsigned>> findTriggles(std::vector<Decision> partnerDecision);
		static bool timeToDefect(unsigned turn, std::vector<std::tuple<unsigned,unsigned>> triggles);
};

class SoftMajority: public Strategy
{
	public:
		SoftMajority(void)
			: Strategy(
					"Soft Majority",
					"SM",
					"Cooperates as long as the number of defections of the partner is not greater than the number of cooperations."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class HardMajority: public Strategy
{
	public:
		HardMajority(void)
			: Strategy(
					"Hard Majority",
					"HM",
					"Defects as long as the number of cooperations of the partner is not greater than the number of defections."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
};

class NaiveProber: public Strategy
{
	public:
		NaiveProber(double probabilityOfDefecting = 0.10);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
	private:
		double probabilityOfDefecting;
		bool randomlyDefect(void);
};

class RemorsefulProber: public Strategy
{
	public:
		RemorsefulProber(double probabilityOfProbing = 0.10);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
	private:
		double probabilityOfProbing;
		bool wasProbing(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision);
		bool probePartner(void);

};

class SoftGrudger: public Strategy
{
	public:
		SoftGrudger(void)
			: Strategy(
					"Soft Grudger",
					"SG",
					"After a partner defection, react with D,D,D,D,C,C."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
	private:
		std::vector<unsigned> findTriggles(std::vector<Decision> partnerDecision);
		bool                  timeToDefect(unsigned turn, std::vector<unsigned> triggles);
};

class Prober: public Strategy
{
	public:
		Prober(void)
			: Strategy(
					"Prober",
					"PB",
					"Start with D,C,C. If the partner cooperated in the second and third move, always defect afterward. Play tit for tat otherwise."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) final;
	private:
		Decision initialDecision(unsigned turn);
		bool     defectionBehavior(std::vector<Decision> partnerDecision);
};

extern AlwaysCooperate  allC;
extern AlwaysDefect     allD;
extern TitForTat        tft ;
extern RandomStrategy   randS;
extern GrimTrigger      grim;
extern Pavlov           pvl;
extern TitForTwoTats    tftt;
extern GradualS         gradualS;
extern SoftMajority     sm;
extern HardMajority     hm;
extern NaiveProber      np;
extern RemorsefulProber rp;
extern SoftGrudger      sg;
extern Prober           pb;

#endif
