// TODO: add more `return` statements
// when it makes sense to do so.

#include <cstddef>
#include <random>
#include <iterator>
#include <utility>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include "Strategies.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"

AlwaysCooperate                  allC;
AlwaysDefect                     allD;
Lunatic                          moon;
GrimTrigger                      grim;
Pavlov                           pvl;
Gradual                          gradual;
SoftMajority                     sm;
HardMajority                     hm;
NaiveProber                      np;
RemorsefulProber                 rp;
SoftGrudger                      sg;
Prober                           pb;
FirmButFair                      fbf;
TitForTat                        tft;
TitForTwoTats                    tftt;
TwoTitsForTat                    ttft;
ReverseTitForTat                 rtft;
GenerousTitForTat                gtft;
SuspiciousTitForTat              stft;
HardTitForTat                    htft;
AdaptativeTitForTat              atft;
MetaRegulatedAdaptativeTitForTat mratft;

const std::vector<const Strategy *> allStrategies =
{
	& allC,
	& allD,
	& moon,
	& grim,
	& pvl,
	& gradual,
	& sm,
	& hm,
	& np,
	& rp,
	& sg,
	& pb,
	& fbf,
	& tft,
	& tftt,
	& ttft,
	& rtft,
	& gtft,
	& stft,
	& htft,
	& atft,
	& mratft,
};

const Strategy * findStrategy(
	std::string name,
	std::string shortName,
	std::string description
){
	auto isDesiredStrategy = [&](const Strategy * const strategy) -> bool
		{ return ( (strategy->name        == name)        &&\
		           (strategy->shortName   == shortName)   &&\
		           (strategy->description == description) ); };
	auto foundStrategy = std::find_if(
		allStrategies.cbegin(),
		allStrategies.cend(),
		isDesiredStrategy);
	return (foundStrategy!=allStrategies.cend()) ? *foundStrategy : nullptr;
}

// [Instructions for how to implement a ]
// class ClassName [All in capital letters]: public Strategy [Always a plublic Strategy]
// {
// 	public:
// 		Constructor(void) [Constructor, set name, shortName, and description.]
// 			: Strategy(
// 					"Class Name",        [All words start with a capital letter.                   ]
// 					"AllC",              [Short name start with a capital letter. No space present.]
// 					"Always cooperate.") [Description as a phrase. Ends with a full stop.          ]
// 					{}
// 		Decision makeDecision(
// 			const std::vector<Decision> & thisDecision,
// 			const std::vector<Decision> & partnerDecision) const override final;
// 	private:
// 		[All auxiliar methods and variables must be kept]
// 		[private.                                       ]
// 		[Strategies must not keep any sort of           ]
// 		[status, the 'makeDecision' function has to be  ]
// 		[like a mathematical fucntion, it must have only]
// 		[one output for a given input.                  ]
// };

Decision AlwaysCooperate::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	return Decision::cooperate;
}

Decision AlwaysDefect::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	return Decision::defect;
}

Decision Lunatic::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	static std::default_random_engine randomGenerator;
	static std::uniform_int_distribution<size_t> uniformDistribution(0, 1);
	return static_cast<Decision>( uniformDistribution(randomGenerator) );
}

Decision GrimTrigger::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	return std::any_of(partnerDecision.cbegin(), partnerDecision.cend(), [](const Decision d){return d==Decision::defect;})
		? Decision::defect
		: Decision::cooperate ;
}

Decision Pavlov::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if(thisDecision.empty()) return Decision::cooperate;
	return Pavlov::decideBasedOnPayoff(thisDecision.back(), partnerDecision.back());
}

Decision Pavlov::decideBasedOnPayoff(
	const Decision & thisLastDecision,
	const Decision & partnerLastDecision
)
{
	const Payoff lastPayoff = PayoffComputer::left(thisLastDecision, partnerLastDecision);
	return ((lastPayoff==Payoff::temptation) || (lastPayoff==Payoff::reward ))
		? thisLastDecision
		: !thisLastDecision;
}


Decision Gradual::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = thisDecision.size();
	return
		Gradual::isTimeToDefect(currentTurn, Gradual::lastTurnsWhenDefectionTriggedReaction(partnerDecision))
		? Decision::defect
		: Decision::cooperate;
}

std::pair<size_t,size_t> Gradual::lastTurnsWhenDefectionTriggedReaction(const std::vector<Decision> & partnerDecision)
{
	size_t lastTurnsOfReactionTrigged               = 0;
	size_t numberOfDefectionsWhenReactionWasTrigged = 0;
	for (size_t turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			lastTurnsOfReactionTrigged                     = turn;
			numberOfDefectionsWhenReactionWasTrigged       = Gradual::countDefectsUntil(turn, partnerDecision);
			const size_t numberOfCooperationsAfterDefecting = 2;
			turn += numberOfDefectionsWhenReactionWasTrigged + numberOfCooperationsAfterDefecting;
		}
	}
	return std::pair(lastTurnsOfReactionTrigged,numberOfDefectionsWhenReactionWasTrigged);
}

size_t Gradual::countDefectsUntil(const size_t turn, const std::vector<Decision> & partnerDecision)
{
	return static_cast<size_t>( std::count(
		partnerDecision.cbegin(),
		std::next(partnerDecision.cbegin(), static_cast<ptrdiff_t>(turn + 1)),
		Decision::defect
	));
}

bool Gradual::isTimeToDefect(const size_t currentTurn, const std::pair<size_t,size_t> & turnAndDefectionCount)
{
	auto [lastTurnsOfReactionTrigged, numberOfDefectionsWhenReactionWasTrigged] = turnAndDefectionCount;
	return
		((currentTurn > lastTurnsOfReactionTrigged) && (currentTurn <= (lastTurnsOfReactionTrigged + numberOfDefectionsWhenReactionWasTrigged)) )
		? true
		: false;
}

Decision SoftMajority::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	auto numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	auto numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfCooperates >= numberOfDefects) ? Decision::cooperate : Decision::defect;
}

Decision HardMajority::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	auto numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	auto numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfDefects >= numberOfCooperates) ? Decision::defect : Decision::cooperate;
}

const std::vector<Decision> SoftGrudger::reactionToDefection = {
	Decision::defect   ,
	Decision::defect   ,
	Decision::defect   ,
	Decision::defect   ,
	Decision::cooperate,
	Decision::cooperate
};

Decision SoftGrudger::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = partnerDecision.size();
	const size_t lastTurnsOfReactionTrigged = SoftGrudger::lastTurnsWhenDefectionTriggedReaction(partnerDecision);
	return SoftGrudger::isTimeToReact(currentTurn, lastTurnsOfReactionTrigged)
		? SoftGrudger::reactionToDefection.at(currentTurn - lastTurnsOfReactionTrigged - 1)
		: Decision::cooperate;
}

size_t SoftGrudger::lastTurnsWhenDefectionTriggedReaction(const std::vector<Decision> & partnerDecision)
{
	size_t lastTurnsOfReactionTrigged = std::numeric_limits<size_t>::max();
	for (size_t turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			lastTurnsOfReactionTrigged = turn;
			turn += SoftGrudger::reactionToDefection.size() - 1;
			// the `-1` is because of the `++turn`.
		}
	}
	return lastTurnsOfReactionTrigged;
}

bool SoftGrudger::isTimeToReact(const size_t currentTurn, const size_t lastTurnsOfReactionTrigged)
{
	return ((currentTurn > lastTurnsOfReactionTrigged) &&
	       (currentTurn <= (lastTurnsOfReactionTrigged + SoftGrudger::reactionToDefection.size())) )
	       ? true
	       : false;
}

const std::vector<Decision> Prober::initialDecisions = {Decision::defect, Decision::cooperate, Decision::cooperate};

// TODO: reduce the size of this implementation.
Decision Prober::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = thisDecision.size();
	if      ( Prober::isTurnOfInitialDecision(currentTurn) ) return Prober::initialDecisions.at(currentTurn);
	else if (Prober::defectionBehavior(partnerDecision))     return Decision::defect;
	else                                                     return partnerDecision.back(); // Tit for tat behavior
}

bool Prober::isTurnOfInitialDecision(const size_t turn)
{
	return turn <= (Prober::initialDecisions.size() - 1);
}

bool Prober::defectionBehavior(const std::vector<Decision> & partnerDecision)
{
	const auto secondDecision = partnerDecision.at(1);
	const auto thirdDecision  = partnerDecision.at(2);
	return (secondDecision==Decision::cooperate) && (thirdDecision==Decision::cooperate);
}

Decision FirmButFair::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	if (partnerDecision.empty())                                               return Decision::cooperate;
	if (FirmButFair::gotAsuckers(thisDecision.back(), partnerDecision.back())) return Decision::defect;
	else                                                                       return Decision::cooperate;
}

bool FirmButFair::gotAsuckers(const Decision & thisLastDecision, const Decision & partnerLastDecision)
{
	return PayoffComputer::left(thisLastDecision, partnerLastDecision) == Payoff::suckers;
}

Decision TitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if (partnerDecision.empty()) return Decision::cooperate;
	return partnerDecision.back();
}

Decision TitForTwoTats::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = partnerDecision.size();
	const size_t requiredDefectionsInARow = 2;
	if ((currentTurn < requiredDefectionsInARow)) return Decision::cooperate;
	auto isDefection = [](const Decision & d) -> bool {return d==Decision::defect;};
	return std::all_of(partnerDecision.cend()-requiredDefectionsInARow, partnerDecision.cend(), isDefection)
		? Decision::defect
		: Decision::cooperate;
}

Decision TwoTitsForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = partnerDecision.size();
	const size_t numberOfPreviousDecisionsToLookForADefection = 2;
	auto start = partnerDecision.cend() - static_cast<ptrdiff_t>(std::min(currentTurn, numberOfPreviousDecisionsToLookForADefection));
	auto end   = partnerDecision.cend();
	auto isDefection = [](const Decision & d) -> bool {return d==Decision::defect;};
	return std::any_of(start, end, isDefection)
		? Decision::defect
		: Decision::cooperate;
}

NaiveProber::NaiveProber(double probabilityOfDefecting)
	: Strategy(
			"Naive Prober",
			"NP",
			"Like Tit for Tat, but ocasionally defects with a small probability."),
	  probabilityOfDefecting(probabilityOfDefecting)
{
	if ((this->probabilityOfDefecting < 0.0) || (1.0 < this->probabilityOfDefecting))
		throw std::domain_error("Probability of defecting in Naive Prober has to be between 0.0 and 1.0.");
}

Decision NaiveProber::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if      (this->decidedRandomlyToDefect()) return Decision::defect      ;
	else if (partnerDecision.empty())         return Decision::cooperate   ;
	else                                      return partnerDecision.back();
}

bool NaiveProber::decidedRandomlyToDefect(void) const
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfDefecting;
}

RemorsefulProber::RemorsefulProber(double probabilityOfProbing)
	: Strategy(
			"Remorseful Prober",
			"RP",
			"If the partner cooperates, prober it with a certain probability. If the partner defects, cooperates if that was caused by a probation, defects otherwise."),
	  probabilityOfProbing(probabilityOfProbing)
{
	if ((this->probabilityOfProbing < 0.0) || (1.0 < this->probabilityOfProbing))
		throw std::domain_error("Probability of probing in Remorseful Prober has to be between 0.0 and 1.0.");
}

Decision RemorsefulProber::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if (thisDecision.empty())
		return Decision::cooperate;
	if (partnerDecision.back() == Decision::defect)
	{
		return RemorsefulProber::wasProbing(thisDecision, partnerDecision)
			? Decision::cooperate
			: Decision::defect;
	}
	else // partnerDecision.back() == Decision::cooperate
	{
		return this->probePartner()
			? Decision::defect
			: Decision::cooperate;
	}
}

bool RemorsefulProber::wasProbing(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	if (thisDecision.size()>=2)
	{
		const Decision probationDecision             = *(thisDecision.cend()    - 2);
		const Decision partnerAnswerPriorToProbation = *(partnerDecision.cend() - 2);
		const Decision partnerAnswerToProbation      = *(partnerDecision.cend() - 1);
		// Situation:
		// this::    {D, *}
		// partner:: {C, D}
		if ((probationDecision             == Decision::defect   ) &&
			(partnerAnswerToProbation      == Decision::defect   ) &&
			(partnerAnswerPriorToProbation == Decision::cooperate)
		   )
			return true;
	}
	return false;
}

bool RemorsefulProber::probePartner(void) const
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfProbing;
}

GenerousTitForTat::GenerousTitForTat(double probabilityOfCooperating)
	: Strategy(
		"Generous Tit For Tat",
		"GTFT",
		"Like Tit for Tat, but after the partner defects, it cooperates with a small probability."
	  ),
	  probabilityOfCooperating(probabilityOfCooperating)
{
	if ((this->probabilityOfCooperating < 0.0) || (1.0 < this->probabilityOfCooperating))
		throw std::domain_error("Probability of cooperating in Generous Tit for Tat has to be between 0.0 and 1.0.");
}

Decision GenerousTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if      (partnerDecision.empty())            return Decision::cooperate   ;
	else if (this->decidedRandomlyToCooperate()) return Decision::cooperate   ;
	else                                         return partnerDecision.back();
}

bool GenerousTitForTat::decidedRandomlyToCooperate(void) const {
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfCooperating;
}

Decision SuspiciousTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if (partnerDecision.empty()) return Decision::defect;
	return partnerDecision.back();
}

Decision HardTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	const size_t currentTurn = partnerDecision.size();
	const size_t numberOfPreviousDecisionsToLookForADefection = 3;
	auto start = partnerDecision.cend() - static_cast<ptrdiff_t>(std::min(currentTurn, numberOfPreviousDecisionsToLookForADefection));
	auto end   = partnerDecision.cend();
	auto isDefection = [](const Decision & d) -> bool {return d==Decision::defect;};
	return std::any_of(start, end, isDefection)
		? Decision::defect
		: Decision::cooperate;
}

Decision ReverseTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	if (partnerDecision.empty()) return Decision::defect;
	return !partnerDecision.back();
}

AdaptativeTitForTat::AdaptativeTitForTat(const double worldZero, const double adaptationRate)
	: Strategy(
		"Adaptative Tit For Tat",
		"ATFT",
		"Check the paper 'Toward Adaptive Cooperative Behavior' of the author 'Elpida S. Tzafestas'."
	  ),
	  worldZero(worldZero),
	  adaptationRate(adaptationRate)
{
	if ((this->worldZero>1) || (this->worldZero<0))
		throw std::domain_error("World Zero in Adaptative Tit For Tat must be in the interval [0,1].");
	if ((this->adaptationRate>1) || (this->adaptationRate<0))
		throw std::domain_error("Adaptation Rate in Adaptative Tit For Tat must be in the interval [0,1].");
	return;
}

Decision AdaptativeTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	static const double worldCutoffValue = 0.50;
	double world = AdaptativeTitForTat::computeWorld(partnerDecision);
	return (world>=worldCutoffValue) ? Decision::cooperate : Decision::defect;
}

double AdaptativeTitForTat::computeWorld(const std::vector<Decision> & partnerDecision) const
{
	double world = this->worldZero;
	for (auto decision: partnerDecision)
	{
		world = (decision == Decision::cooperate) ?
			    world + this->adaptationRate * (1 - world) :
			    world + this->adaptationRate * (0 - world) ;
	}
	return world;
}

MetaRegulatedAdaptativeTitForTat::MetaRegulatedAdaptativeTitForTat(
	const double worldZero                    ,
	const double adaptationRateCooperationZero,
	const double adaptationRateDefectionZero  ,
	const double adaptationRateMinimum        ,
	const double adaptationRateMaximum        ,
	const size_t adaptationWindow           ,
	const size_t adaptationThreshold
)
	: Strategy(
		"Meta-Regulated Adaptative Tit For Tat",
		"MRATFT",
		"Check the paper 'Toward Adaptive Cooperative Behavior' of the author 'Elpida S. Tzafestas'."
	  ),
	  worldZero                     (worldZero                    ),
	  adaptationRateCooperationZero (adaptationRateCooperationZero),
	  adaptationRateDefectionZero   (adaptationRateDefectionZero  ),
	  adaptationRateMinimum         (adaptationRateMinimum        ),
	  adaptationRateMaximum         (adaptationRateMaximum        ),
	  adaptationWindow              (adaptationWindow             ),
	  adaptationThreshold           (adaptationThreshold          )
{
	if ((this->worldZero                    >1) || (this->worldZero                     <0))
		throw std::domain_error("World Zero in Adaptative Tit For Tat must be in the interval [0,1].");
	if ((this->adaptationRateCooperationZero>1) || (this->adaptationRateCooperationZero <0))
		throw std::domain_error("Cooperative Adaptation Rate Zero in Meta-Regulated Adaptative Tit For Tat must be in the interval [0,1].");
	if ((this->adaptationRateDefectionZero  >1) || (this->adaptationRateDefectionZero   <0))
		throw std::domain_error("Defection Adaptation Rate Zero in Meta-Regulated Adaptative Tit For Tat must be in the interval [0,1].");
	if ((this->adaptationRateMinimum        >1) || (this->adaptationRateMinimum         <0))
		throw std::domain_error("Defection Adaptation Rate Minimum in Meta-Regulated Adaptative Tit For Tat must be in the interval [0,1].");
	if ((this->adaptationRateMaximum        >1) || (this->adaptationRateMaximum         <0))
		throw std::domain_error("Defection Adaptation Rate Maximum in Meta-Regulated Adaptative Tit For Tat must be in the interval [0,1].");
	if (this->adaptationThreshold           > this->adaptationWindow)
		throw std::domain_error("Adaptation Threshold has to be smaller of equals to Adaptation Window.");
	return;
}

Decision MetaRegulatedAdaptativeTitForTat::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	double world = this->computeWorld(thisDecision, partnerDecision);
	return (world>=0.5) ? Decision::cooperate : Decision::defect;
}

double MetaRegulatedAdaptativeTitForTat::computeWorld(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	double world                     = this->worldZero;
	double adaptationRateCooperation = this->adaptationRateCooperationZero;
	double adaptationRateDefection   = this->adaptationRateDefectionZero;
	size_t thresholdCount            = 0;
	for (size_t turn=0u ; turn<partnerDecision.size() ; ++turn)
	{
		this->updateAdaptationRate(turn, thresholdCount, adaptationRateCooperation, adaptationRateDefection);
		this->updateThresholdCount(turn, thresholdCount, thisDecision.at(turn), partnerDecision.at(turn));
		world = this->updateWorld(world, partnerDecision.at(turn), adaptationRateCooperation, adaptationRateDefection);
	}
	return world;
}

void MetaRegulatedAdaptativeTitForTat::updateAdaptationRate(
	const size_t turn,
	const size_t thresholdCount,
	double &     adaptationRateCooperation,
	double &     adaptationRateDefection
) const
{
	if (turn!=0u) // It is annoying, the case `turn = 0` has to be excluded.
	{
		if ((turn % (this->adaptationWindow-1)) == 0) // `-1` because it starts at 0
		{
			if (thresholdCount > this->adaptationThreshold)
			{
				adaptationRateCooperation = this->adaptationRateMinimum;
				adaptationRateDefection   = this->adaptationRateMaximum;
			}
			else
			{
				adaptationRateCooperation = this->adaptationRateMaximum;
				adaptationRateDefection   = this->adaptationRateMinimum;
			}
		}
	}
	return;
}

void MetaRegulatedAdaptativeTitForTat::updateThresholdCount(
	const size_t     turn,
	size_t &         thresholdCount,
	const Decision & thisDecision,
	const Decision & partnerDecision
) const
{
	if ((turn % (this->adaptationWindow-1)) == 0)
		thresholdCount = 0u;
	if(thisDecision == partnerDecision)
		++thresholdCount;
	return;
}

double MetaRegulatedAdaptativeTitForTat::updateWorld(
	double           world,
	const Decision & partnerDecision,
	const double     adaptationRateCooperation,
	const double     adaptationRateDefection
) const
{
	return (partnerDecision == Decision::cooperate)
		? world + adaptationRateCooperation * (1 - world)
		: world + adaptationRateDefection   * (0 - world);
}
