#include <Strategies.hpp>
#include <Payoff.hpp>
#include <random>
#include <algorithm>
#include <stdexcept>

AlwaysCooperate  allC;
AlwaysDefect     allD;
TitForTat        tft;
RandomStrategy   randS;
GrimTrigger      grim;
Pavlov           pvl;
TitForTwoTats    tftt;
GradualS         gradualS;
SoftMajority     sm;
HardMajority     hm;
NaiveProber      np;
RemorsefulProber rp;
SoftGrudger      sg;
Prober           pb;

Decision AlwaysCooperate::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	return Decision::cooperate;
}

Decision AlwaysDefect::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	return Decision::defect;
}

Decision TitForTat::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	Decision decision;
	if (thisDecision.size()==0)
		decision = Decision::cooperate;
	else
		decision = partnerDecision.back();
	return decision;
}

Decision RandomStrategy::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	static std::default_random_engine randomGenerator;
	static std::uniform_int_distribution<unsigned> uniformDistribution(0, 1);
	return static_cast<Decision>( uniformDistribution(randomGenerator) );
}

Decision GrimTrigger::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	Decision decision;
	if ( std::any_of(partnerDecision.begin(), partnerDecision.end(), [](Decision d){return d==Decision::defect;}) )
		decision = Decision::defect;
	else
		decision = Decision::cooperate;
	return decision;
}

Decision Pavlov::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
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

Decision TitForTwoTats::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
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

Decision GradualS::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	Decision decision;
	auto triggles = GradualS::findTriggles(partnerDecision);
	if (GradualS::timeToDefect(thisDecision.size(), triggles))
		decision = Decision::defect;
	else // time to cooperate incorporated in 'findTrigges' algorithm.
		decision = Decision::cooperate;
	return decision;
}

std::vector<std::tuple<unsigned,unsigned>> GradualS::findTriggles(
	std::vector<Decision> partnerDecision)
{
	std::vector<std::tuple<unsigned,unsigned>> triggles;
	for (unsigned turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			unsigned numberOfDefects = static_cast<unsigned>(std::count(partnerDecision.cbegin(), partnerDecision.cbegin()+turn+1, Decision::defect));
			triggles.push_back({turn, numberOfDefects});
			turn += numberOfDefects + 2;
		}
	}
	return triggles;
}

bool GradualS::timeToDefect(unsigned turn, std::vector<std::tuple<unsigned,unsigned>> triggles)
{
	bool defect = false;
	for (auto& triggle: triggles)
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
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	unsigned numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	unsigned numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfDefects > numberOfCooperates) ? Decision::defect : Decision::cooperate;
}

Decision HardMajority::makeDecision(
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
{
	unsigned numberOfDefects    = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::defect   );
	unsigned numberOfCooperates = std::count(partnerDecision.cbegin(), partnerDecision.cend(), Decision::cooperate);
	return (numberOfCooperates > numberOfDefects) ? Decision::cooperate : Decision::defect;
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
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
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

bool NaiveProber::randomlyDefect(void)
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
	[[maybe_unused]] std::vector<Decision> thisDecision,
	[[maybe_unused]] std::vector<Decision> partnerDecision
)
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
	std::vector<Decision> thisDecision,
	std::vector<Decision> partnerDecision
)
{
	bool wasProbing = false;
	Decision probationDecision, partnerAnswerToProbation, partnerAnswerPriorToProbation;
	if (thisDecision.size()>=2)
	{
		probationDecision             = *(thisDecision.crbegin() + 1);
		partnerAnswerPriorToProbation = *(partnerDecision.crbegin() + 1);
		partnerAnswerToProbation      = *partnerDecision.crbegin();
		// Situation:
		// this::    {D, *}
		// partner:: {C, D}
		if ((probationDecision==Decision::defect) && (partnerAnswerToProbation==Decision::defect) && (partnerAnswerPriorToProbation==Decision::cooperate))
			wasProbing = true;
	}
	return wasProbing;
}

bool RemorsefulProber::probePartner(void)
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfProbing;
}

Decision SoftGrudger::makeDecision(
	std::vector<Decision> thisDecision,
	std::vector<Decision> partnerDecision
)
{
	Decision decision;
	auto triggles = SoftGrudger::findTriggles(partnerDecision);
	if (SoftGrudger::timeToDefect(thisDecision.size(), triggles))
		decision = Decision::defect;
	else // time to cooperate incorporated in 'findTrigges' algorithm.
		decision = Decision::cooperate;
	return decision;
}

std::vector<unsigned> SoftGrudger::findTriggles(std::vector<Decision> partnerDecision)
{
	std::vector<unsigned> triggles;
	for (unsigned turn=0 ; turn<partnerDecision.size() ; ++turn)
	{
		if (partnerDecision.at(turn) == Decision::defect)
		{
			triggles.push_back(turn);
			turn += 6;
		}
	}
	return triggles;
}

bool SoftGrudger::timeToDefect(unsigned turn, std::vector<unsigned> triggles)
{
	bool defect = false;
	for (auto& triggleTurn: triggles)
	{
		if ( (turn > triggleTurn) && (turn <= triggleTurn + 4) )
		{
			defect = true;
			break;
		}
	}
	return defect;
}

Decision Prober::makeDecision(
	std::vector<Decision> thisDecision,
	std::vector<Decision> partnerDecision
)
{
	Decision decision;
	unsigned turn = thisDecision.size();
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

Decision Prober::initialDecision(unsigned turn)
{
	static std::vector<Decision> initialDecisions = {Decision::defect, Decision::cooperate, Decision::cooperate};
	return initialDecisions.at(turn);
}

bool Prober::defectionBehavior(std::vector<Decision> partnerDecision)
{
	auto secondDecision = *(partnerDecision.cbegin() + 1);
	auto thirdDecision  = *(partnerDecision.cbegin() + 2);
	return (secondDecision==Decision::cooperate) && (thirdDecision==Decision::cooperate);
}
