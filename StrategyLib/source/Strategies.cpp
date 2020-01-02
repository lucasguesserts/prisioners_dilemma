#include <Strategies.hpp>
#include <random>

AlwaysCooperate allC;
AlwaysDefect    allD;
TitForTat       tft;
RandomStrategy  randS;

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
