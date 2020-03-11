#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

// Based on http://www.prisoners-dilemma.com/strategies.html

#include <cstddef>
#include <utility>
#include <vector>
#include <string>
#include "Strategy.hpp"
#include "Decision.hpp"

namespace PrisonersDilemma
{

	// TODO: this solution works but might not
	// be the best one. Check how to correctly
	// implement a factory class in C++
	template <class Class, class Interface>
	class Factory
	{
		public:
				static std::unique_ptr<Interface> create(void){
					// TODO: allow passing arguments to the function
					// or define the function already with its
					// arguments when passing to a player.
					return std::move(Class::createInternal());
				}
	};

	class AlwaysCooperate:
		public Factory<AlwaysCooperate, Strategy>,
		public Strategy
	{
		public:
			AlwaysCooperate(void)
				: Strategy(
						"Always Cooperate",
						"AllC",
						"Always cooperate."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
			static std::unique_ptr<Strategy> createInternal(void)
			{
				// TODO: I get and error with std::make_unique. Correct it.
				return std::unique_ptr<Strategy>(new AlwaysCooperate);
			}
	};

	class AlwaysDefect:
		public Factory<AlwaysDefect, Strategy>,
		public Strategy
	{
		public:
			AlwaysDefect(void)
				: Strategy(
						"Always Defect",
						"AllD",
						"Always defect."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
			static std::unique_ptr<Strategy> createInternal(void)
			{
				return std::unique_ptr<Strategy>(new AlwaysDefect);
			}
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			static Decision decideBasedOnPayoff(
				const Decision & thisLastDecision,
				const Decision & partnerLastDecision);
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			static std::pair<size_t,size_t> lastTurnsWhenDefectionTriggedReaction(const std::vector<Decision> & partnerDecision);
			static size_t                   countDefectsUntil(const size_t turn, const std::vector<Decision> & partnerDecision);
			static bool                     isTimeToDefect(const size_t currentTurn, const std::pair<size_t,size_t> & turnAndDefectionCount);
	};

	class SoftMajority: public Strategy
	{
		public:
			SoftMajority(void)
				: Strategy(
						"Soft Majority",
						"SM",
						"Cooperates as long as the number of cooperations of the partner is greater or equals to the number of defections."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
	};

	class HardMajority: public Strategy
	{
		public:
			HardMajority(void)
				: Strategy(
						"Hard Majority",
						"HM",
						"Defects as long as the number of defections of the partner is greater than or equals to the number of cooperations."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
	};

	class SoftGrudger: public Strategy
	{
		// TODO: remove the magic numbers 4 and 6 from its implementation.
		public:
			SoftGrudger(void)
				: Strategy(
						"Soft Grudger",
						"SG",
						"After a partner defection, react with D,D,D,D,C,C."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			static const std::vector<Decision> reactionToDefection;
			static size_t                      lastTurnsWhenDefectionTriggedReaction(const std::vector<Decision> & partnerDecision);
			static bool                        isTimeToReact(const size_t currentTurn, const size_t lastTurnsOfReactionTrigged);
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			static bool     isTurnOfInitialDecision(const size_t turn);
			static bool     defectionBehavior(const std::vector<Decision> & partnerDecision);
			static const std::vector<Decision> initialDecisions; 
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			static bool gotAsuckers(const Decision & thisLastDecision, const Decision & partnerLastDecision);
	};

	class TitForTat:
		public Factory<TitForTat, Strategy>,
		public Strategy
	{
		public:
			TitForTat(void)
				: Strategy(
						"Tit For Tat",
						"TFT",
						"Start cooperating. Copy opponent's last move afterwards."){}
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
			static std::unique_ptr<Strategy> createInternal(void)
			{
				return std::unique_ptr<Strategy>(new TitForTat);
			}
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
	};

	class NaiveProber: public Strategy
	{
		public:
			NaiveProber(double probabilityOfDefecting = 0.10);
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			const double probabilityOfDefecting;
			bool decidedRandomlyToDefect(void) const;
	};

	class RemorsefulProber: public Strategy
	{
		public:
			RemorsefulProber(double probabilityOfProbing = 0.10);
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			const double probabilityOfProbing;
			bool wasProbing(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const;
			bool probePartner(void) const;
	};

	class GenerousTitForTat: public Strategy
	{
		public:
			GenerousTitForTat(double probabilityOfCooperating = 0.1);
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			double probabilityOfCooperating;
			bool decidedRandomlyToCooperate(void) const;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
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
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
	};

	class AdaptativeTitForTat: public Strategy
	{
		public:
			AdaptativeTitForTat(const double worldZero = 0.50, const double adaptationRate = 0.20);
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			const double worldZero;
			const double adaptationRate;
			double computeWorld(const std::vector<Decision> & partnerDecision) const;
	};

	class MetaRegulatedAdaptativeTitForTat: public Strategy
	{
		public:
			MetaRegulatedAdaptativeTitForTat(
				const double worldZero                     = 0.50,
				const double adaptationRateCooperationZero = 0.20,
				const double adaptationRateDefectionZero   = 0.20,
				const double adaptationRateMinimum         = 0.10,
				const double adaptationRateMaximum         = 0.30,
				const size_t adaptationWindow              = 10,
				const size_t adaptationThreshold           = 2);
			Decision makeDecision(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const override final;
		private:
			const double worldZero;
			const double adaptationRateCooperationZero;
			const double adaptationRateDefectionZero;
			const double adaptationRateMinimum;
			const double adaptationRateMaximum;

			const size_t adaptationWindow;
			const size_t adaptationThreshold;

			double computeWorld(
				const std::vector<Decision> & thisDecision,
				const std::vector<Decision> & partnerDecision) const;
			void updateAdaptationRate(
				const size_t turn,
				const size_t thresholdCount,
				double &  adaptationRateCooperation,
				double &  adaptationRateDefection) const;
			void updateThresholdCount(
				const size_t turn,
				size_t & thresholdCount,
				const Decision & thisDecision,
				const Decision & partnerDecision) const;
			double updateWorld(
				double           world,
				const Decision & partnerDecision,
				const double     adaptationRateCooperation,
				const double     adaptationRateDefection) const;
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
	extern const std::vector<const Strategy *> allStrategies;

	const Strategy * findStrategy(
		std::string name,
		std::string shortName,
		std::string description);

}

#endif
