#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <cstddef>
#include <vector>
#include <tuple>
#include <string>
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
			std::vector<Decision> partnerDecision) override final;
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
			std::vector<Decision> partnerDecision) override final;
};

class Lunatic: public Strategy
{
	public:
		Lunatic(void)
			: Strategy(
					"Lunatic",
					"Moon",
					"Cooperate or defect with equal probabilities."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class GrimTrigger: public Strategy
{
	public:
		GrimTrigger(void)
			: Strategy(
					"Grim Trigger",
					"Grim",
					"Cooperates until the partner defects. Thereafter it only defects."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
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
			std::vector<Decision> partnerDecision) override final;
};

class Gradual: public Strategy
{
	public:
		Gradual(void)
			: Strategy(
					"Gradual",
					"Gradual",
					"Start cooperating. When the partner defects, it defects as many times as the partner has defected and then cooperates twice."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
	private:
		static std::vector<std::tuple<unsigned,unsigned>> findTriggles(std::vector<Decision> partnerDecision);
		static bool timeToDefect(size_t turn, std::vector<std::tuple<unsigned,unsigned>> triggles);
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
			std::vector<Decision> partnerDecision) override final;
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
			std::vector<Decision> partnerDecision) override final;
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
			std::vector<Decision> partnerDecision) override final;
	private:
		std::vector<unsigned> findTriggles(std::vector<Decision> partnerDecision);
		bool                  timeToDefect(size_t turn, std::vector<unsigned> triggles);
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
			std::vector<Decision> partnerDecision) override final;
	private:
		Decision initialDecision(size_t turn);
		bool     defectionBehavior(std::vector<Decision> partnerDecision);
};

class FirmButFair: public Strategy
{
	public:
		FirmButFair(void)
			: Strategy(
					"Firm But Fair",
					"FBF",
					"Defects only after receiving a sucker's payoff."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class TitForTat: public Strategy
{
	public:
		TitForTat(void)
			: Strategy(
					"Tit For Tat",
					"TFT",
					"Start cooperating. Copy opponent's last move afterwards."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class TitForTwoTats: public Strategy
{
	public:
		TitForTwoTats(void)
			: Strategy(
					"Tit For Two Tats",
					"TFTT",
					"Start cooperating. Defects when the partner defects twice in a row."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class TwoTitsForTat: public Strategy
{
	public:
		TwoTitsForTat(void)
			: Strategy(
					"Two Tits For Tat",
					"TTFT",
					"Start cooperating. Defects if any of the two last decisions of the partner was to defect."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class NaiveProber: public Strategy
{
	public:
		NaiveProber(double probabilityOfDefecting = 0.10);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
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
			std::vector<Decision> partnerDecision) override final;
	private:
		double probabilityOfProbing;
		bool wasProbing(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision);
		bool probePartner(void);
};

class GenerousTitForTat: public Strategy
{
	public:
		GenerousTitForTat(double probabilityOfCooperating = 0.1);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
	private:
		double probabilityOfCooperating;
		bool cooperateAfterDefection(void);
};

class SuspiciousTitForTat: public Strategy
{
	public:
		SuspiciousTitForTat(void)
			: Strategy(
					"Suspicious Tit For Tat",
					"STFT",
					"Start defecting. Copy opponent's last move afterwards."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class HardTitForTat: public Strategy
{
	public:
		HardTitForTat(void)
			: Strategy(
					"Hard Tit For Tat",
					"HTFT",
					"Start cooperating. Defects if the partner has defected in any of the three previous turns."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class ReverseTitForTat: public Strategy
{
	public:
		ReverseTitForTat(void)
			: Strategy(
					"Reverse Tit For Tat",
					"RTFT",
					"Start defecting, then plays the reverse of the partner last decision."){}
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
};

class AdaptativeTitForTat: public Strategy
{
	public:
		AdaptativeTitForTat(double worldZero = 0.500000001, double adaptationRate = 0.2);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
	private:
		double worldZero;
		double adaptationRate;
		double computeWorld(std::vector<Decision> partnerDecision);
};

class MetaRegulatedAdaptativeTitForTat: public Strategy
{
	public:
		MetaRegulatedAdaptativeTitForTat(
			double worldZero                     = 0.50000001,
			double adaptationRateCooperationZero = 0.2,
			double adaptationRateDefectionZero   = 0.2,
			double adaptationRateMinimum         = 0.1,
			double adaptationRateMaximum         = 0.3,
			unsigned adaptationWindow            = 10,
			unsigned adaptationThreshold         = 2);
		Decision makeDecision(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision) override final;
	private:
		double worldZero, adaptationRateCooperationZero, adaptationRateDefectionZero;
		double adaptationRateMinimum, adaptationRateMaximum;
		unsigned adaptationWindow, adaptationThreshold;
		double computeWorld(
			std::vector<Decision> thisDecision,
			std::vector<Decision> partnerDecision);
		void updateAdaptationRate(
			unsigned turn,
			unsigned thresholdCount,
			double&  adaptationRateCooperation,
			double&  adaptationRateDefection);
		void updateThresholdCount(
			unsigned turn,
			unsigned &thresholdCount,
			Decision thisDecision,
			Decision partnerDecision);
		double updateWorld(
			double   world,
			Decision partnerDecision,
			double   adaptationRateCooperation,
			double   adaptationRateDefection);
};

extern AlwaysCooperate                  allC;
extern AlwaysDefect                     allD;
extern Lunatic                          moon;
extern GrimTrigger                      grim;
extern Pavlov                           pvl;
extern Gradual                          gradual;
extern SoftMajority                     sm;
extern HardMajority                     hm;
extern NaiveProber                      np;
extern RemorsefulProber                 rp;
extern SoftGrudger                      sg;
extern Prober                           pb;
extern FirmButFair                      fbf;
extern TitForTat                        tft;
extern TitForTwoTats                    tftt;
extern TwoTitsForTat                    ttft;
extern ReverseTitForTat                 rtft;
extern GenerousTitForTat                gtft;
extern SuspiciousTitForTat              stft;
extern HardTitForTat                    htft;
extern AdaptativeTitForTat              atft;
extern MetaRegulatedAdaptativeTitForTat mratft;

Strategy * findStrategy(
	std::string name,
	std::string shortName,
	std::string description);
extern std::vector<Strategy *> allStrategies;

#endif
