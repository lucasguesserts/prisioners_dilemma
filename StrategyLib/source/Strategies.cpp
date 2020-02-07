#include <cstddef>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <tuple>
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
	const Strategy * found = nullptr;
	for(auto strategy: allStrategies)
	{
		if ( (strategy->name == name) &&\
		     (strategy->shortName == shortName) &&\
		     (strategy->description == description)
		)
		{
			found = strategy;
			break;
		}
	}
	return found;
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
	Decision decision;
	if ( std::any_of(partnerDecision.begin(), partnerDecision.end(), [](Decision d){return d==Decision::defect;}) )
		decision = Decision::defect;
	else
		decision = Decision::cooperate;
	return decision;
}

Decision Pavlov::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.empty())
		decision = Decision::cooperate;
	else
	{
		Payoff lastPayoff = PayoffComputer::left(thisDecision.back(), partnerDecision.back());
		if( (lastPayoff==Payoff::reward) || (lastPayoff==Payoff::temptation ) )
			decision = thisDecision.back();
		else
			decision = !thisDecision.back();
	}
	return decision;
}

const size_t Gradual::numberOfCooperationsAfterDefecting = 2;

Decision Gradual::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	auto triggles = Gradual::findTriggles(partnerDecision);
	if (Gradual::timeToDefect(thisDecision.size(), triggles))
		decision = Decision::defect;
	else // time to cooperate incorporated in 'findTrigges' algorithm.
		decision = Decision::cooperate;
	return decision;
}

std::vector<std::tuple<size_t,size_t>> Gradual::findTriggles(
	const std::vector<Decision> & partnerDecision)
{
	std::vector<std::tuple<size_t,size_t>> triggles;
	for (size_t turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			const size_t countUntil = turn + 1;
			const size_t numberOfDefects = static_cast<size_t>(std::count(partnerDecision.cbegin(), partnerDecision.cbegin()+static_cast<ptrdiff_t>(countUntil), Decision::defect));
			triggles.push_back({turn, numberOfDefects});
			turn += numberOfDefects + Gradual::numberOfCooperationsAfterDefecting;
		}
	}
	return triggles;
}

bool Gradual::timeToDefect(const size_t turn, const std::vector<std::tuple<size_t,size_t>> & triggles)
{
	bool defect = false;
	for (auto & triggle: triggles)
	{
		auto triggleTurn = std::get<0>(triggle);
		auto numberOfDefects = std::get<1>(triggle);
		if ( (turn > triggleTurn) && (turn <= triggleTurn + numberOfDefects) )
		{
			defect = true;
			break;
		}
	}
	return defect;
}

Decision SoftMajority::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	auto numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	auto numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfDefects > numberOfCooperates) ? Decision::defect : Decision::cooperate;
}

Decision HardMajority::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	auto numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	auto numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfCooperates > numberOfDefects) ? Decision::cooperate : Decision::defect;
}

Decision SoftGrudger::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	auto triggles = SoftGrudger::findTriggles(partnerDecision);
	if (SoftGrudger::timeToDefect(thisDecision.size(), triggles))
		decision = Decision::defect;
	else // time to cooperate incorporated in 'findTrigges' algorithm.
		decision = Decision::cooperate;
	return decision;
}

std::vector<size_t> SoftGrudger::findTriggles(const std::vector<Decision> & partnerDecision) const
{
	std::vector<size_t> triggles;
	for (size_t turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			triggles.push_back(turn);
			turn += 6;
		}
	}
	return triggles;
}

bool SoftGrudger::timeToDefect(const size_t turn, const std::vector<size_t> & triggles) const
{
	return std::any_of(
		triggles.cbegin(),
		triggles.cend(),
		[&turn](const size_t triggleTurn){
			return (turn > triggleTurn) && (turn <= triggleTurn + 4);
		});
}

Decision Prober::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	size_t turn = thisDecision.size();
	if (turn<=2)
		decision = Prober::initialDecision(turn); // Start with D,C,C
	else
	{
		if (Prober::defectionBehavior(partnerDecision))
			decision = Decision::defect; // defection behavior
		else
			decision = partnerDecision.back(); // tit for tat behavior
	}
	return decision;
}

Decision Prober::initialDecision(const size_t turn) const
{
	static const std::vector<Decision> & initialDecisions = {Decision::defect, Decision::cooperate, Decision::cooperate};
	return initialDecisions.at(turn);
}

bool Prober::defectionBehavior(const std::vector<Decision> & partnerDecision) const
{
	auto secondDecision = *(partnerDecision.cbegin() + 1);
	auto thirdDecision  = *(partnerDecision.cbegin() + 2);
	return (secondDecision==Decision::cooperate) && (thirdDecision==Decision::cooperate);
}

Decision FirmButFair::makeDecision(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.empty())
		decision = Decision::cooperate;
	else if (PayoffComputer::left(thisDecision.back(), partnerDecision.back()) == Payoff::suckers)
		decision = Decision::defect;
	else
		decision = Decision::cooperate;
	return decision;
}

Decision TitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.size()==0)
		decision = Decision::cooperate;
	else
		decision = partnerDecision.back();
	return decision;
}

Decision TitForTwoTats::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (partnerDecision.size()<2)
		decision = Decision::cooperate;
	else
	{
		if ( (*(partnerDecision.crbegin())==Decision::defect) && (*(partnerDecision.crbegin()+1)==Decision::defect) )
			decision = Decision::defect;
		else
			decision = Decision::cooperate;
	}
	return decision;
}

Decision TwoTitsForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	auto start = std::max(partnerDecision.cbegin(), partnerDecision.cend()-2);
	auto end   = partnerDecision.cend();
	if (partnerDecision.empty())
		decision = Decision::cooperate;
	else if (std::any_of(start, end, [](Decision d){return d==Decision::defect;}))
		decision = Decision::defect;
	else
		decision = Decision::cooperate;
	return decision;
}

NaiveProber::NaiveProber(double probabilityOfDefecting)
	: Strategy(
			"Naive Prober",
			"NP",
			"Like Tit for Tat, but ocasionally defects with a small probability.")
{
	if ((probabilityOfDefecting < 0.0) || (1.0 < probabilityOfDefecting))
		throw std::domain_error("Probability of defecting in Naive Prober has to be between 0.0 and 1.0.");
	this->probabilityOfDefecting = probabilityOfDefecting;
}

Decision NaiveProber::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (this->randomlyDefect())
		decision = Decision::defect;
	else
	{
		if (partnerDecision.size()==0)
			decision = Decision::cooperate;
		else
			decision = partnerDecision.back();
	}
	return decision;
}

bool NaiveProber::randomlyDefect(void) const
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfDefecting;
}

RemorsefulProber::RemorsefulProber(double probabilityOfProbing)
	: Strategy(
			"Remorseful Prober",
			"RP",
			"If the partner cooperates, prober it with a certain probability. If the partner defects, cooperates if that was caused by a probation, defects otherwise.")
{
	if ((probabilityOfProbing < 0.0) || (1.0 < probabilityOfProbing))
		throw std::domain_error("Probability of probing in Remorseful Prober has to be between 0.0 and 1.0.");
	this->probabilityOfProbing = probabilityOfProbing;
}

Decision RemorsefulProber::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.empty())
		decision = Decision::cooperate;
	else
	{
		if (partnerDecision.back() == Decision::defect)
		{
			if (RemorsefulProber::wasProbing(thisDecision, partnerDecision))
				decision = Decision::cooperate;
			else
				decision = Decision::defect;
		}
		else // partnerDecision.back() == Decision::cooperate
		{
			if (this->probePartner())
				decision = Decision::defect;
			else
				decision = Decision::cooperate;
		}
	}
	return decision;
}

bool RemorsefulProber::wasProbing(
	const std::vector<Decision> & thisDecision,
	const std::vector<Decision> & partnerDecision
) const
{
	bool wasProbing = false;
	if (thisDecision.size()>=2)
	{
		const Decision probationDecision             = *(thisDecision.crbegin() + 1);
		const Decision partnerAnswerPriorToProbation = *(partnerDecision.crbegin() + 1);
		const Decision partnerAnswerToProbation      = *partnerDecision.crbegin();
		// Situation:
		// this::    {D, *}
		// partner:: {C, D}
		if ((probationDecision             == Decision::defect   ) &&
			(partnerAnswerToProbation      == Decision::defect   ) &&
			(partnerAnswerPriorToProbation == Decision::cooperate)
		   )
			wasProbing = true;
	}
	return wasProbing;
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
	  )
{
	if ((probabilityOfCooperating < 0.0) || (1.0 < probabilityOfCooperating))
		throw std::domain_error("Probability of cooperating in Generous Tit for Tat has to be between 0.0 and 1.0.");
	this->probabilityOfCooperating = probabilityOfCooperating;
}

Decision GenerousTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.size()==0)
		decision = Decision::cooperate;
	else if (this->cooperateAfterDefection())
		decision = Decision::cooperate; // Cooperate no matter what
	else
		decision = partnerDecision.back(); // Like Tit for Tat
	return decision;
}

bool GenerousTitForTat::cooperateAfterDefection(void) const {
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfCooperating;
}

Decision SuspiciousTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.size()==0)
		decision = Decision::defect;
	else
		decision = partnerDecision.back();
	return decision;
}

Decision HardTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	auto start = std::max(partnerDecision.cbegin(), partnerDecision.cend()-3); // beginning or the third from the end to the beginning
	auto end   = partnerDecision.cend();
	if (thisDecision.size()==0)
		decision = Decision::cooperate;
	else if (std::any_of(start, end, [](Decision d){return d==Decision::defect;}))
		decision = Decision::defect;
	else
		decision = Decision::cooperate;
	return decision;
}

Decision ReverseTitForTat::makeDecision(
	[[maybe_unused]] const std::vector<Decision> & thisDecision,
	[[maybe_unused]] const std::vector<Decision> & partnerDecision
) const
{
	Decision decision;
	if (thisDecision.size()==0)
		decision = Decision::defect;
	else
		decision = ! partnerDecision.back();
	return decision;
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
	if (partnerDecision == Decision::cooperate)
		world = world + adaptationRateCooperation * (1 - world);
	else
		world = world + adaptationRateDefection   * (0 - world);
	return world;
}
