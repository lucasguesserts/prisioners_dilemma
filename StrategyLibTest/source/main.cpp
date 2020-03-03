#define CATCH_CONFIG_MAIN
#include <vector>
#include <cstddef>
#include "Test.hpp"
#include "Decision.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
using namespace PrisonersDilemma;

void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const Strategy & strategy
);

void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const Strategy & strategy
)
{
	check( strategyDecisions.size() == partnerDecisions.size() );
	std::vector<Decision> strategyCummulativeDecisions, partnerCummulativeDecisions;
	for (size_t turn=0 ; turn<strategyDecisions.size() ; ++turn)
	{
		check( strategy.makeDecision(strategyCummulativeDecisions, partnerCummulativeDecisions) == strategyDecisions.at(turn) );
		strategyCummulativeDecisions.push_back(strategyDecisions.at(turn));
		partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
	}
	return;
}
