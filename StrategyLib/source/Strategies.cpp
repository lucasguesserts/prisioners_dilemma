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
