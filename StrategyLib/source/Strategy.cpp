#include <Strategy.hpp>

Strategy::Strategy(void)
	: name(""),
	  shortName(""),
	  description("")
{}

Strategy::Strategy(std::string name, std::string shortName, std::string description)
	: name(name),
	  shortName(shortName),
	  description(description)
{}

void checkDecisionHistory(
	std::vector<Decision> strategyDecisions,
	std::vector<Decision> partnerDecisions,
	Strategy * strategy
)
{
	check( strategyDecisions.size() == partnerDecisions.size() );
	std::vector<Decision> strategyCummulativeDecisions, partnerCummulativeDecisions;
	for (std::vector<Decision>::size_type turn=0 ; turn<strategyDecisions.size() ; ++turn)
	{
		check( strategy->makeDecision(strategyCummulativeDecisions, partnerCummulativeDecisions) == strategyDecisions.at(turn) );
		strategyCummulativeDecisions.push_back(strategyDecisions.at(turn));
		partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
	}
	return;
}
