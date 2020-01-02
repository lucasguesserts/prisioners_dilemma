#include <Strategies.hpp>
#include <Payoff.hpp>
#include <random>
#include <algorithm>

AlwaysCooperate allC;
AlwaysDefect    allD;
TitForTat       tft;
RandomStrategy  randS;
GrimTrigger     grim;
Pavlov          pvl;
TitForTwoTats   tftt;
GradualS        gradualS;
SoftMajority    sm;
HardMajority    hm;

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
