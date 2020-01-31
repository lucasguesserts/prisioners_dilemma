#define CATCH_CONFIG_MAIN
#include <Test.hpp>
#include <Strategies.hpp>

void checkDecisionHistory(
	std::vector<Decision> strategyDecisions,
	std::vector<Decision> partnerDecisions,
	Strategy & strategy
);

void checkDecisionHistory(
	std::vector<Decision> strategyDecisions,
	std::vector<Decision> partnerDecisions,
	Strategy & strategy
)
{
	check( strategyDecisions.size() == partnerDecisions.size() );
	std::vector<Decision> strategyCummulativeDecisions, partnerCummulativeDecisions;
	for (std::vector<Decision>::size_type turn=0 ; turn<strategyDecisions.size() ; ++turn)
	{
		check( strategy.makeDecision(strategyCummulativeDecisions, partnerCummulativeDecisions) == strategyDecisions.at(turn) );
		strategyCummulativeDecisions.push_back(strategyDecisions.at(turn));
		partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
	}
	return;
}
