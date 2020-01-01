#include <Strategies.hpp>

AlwaysCooperate allC;
AlwaysDefect allD;

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
