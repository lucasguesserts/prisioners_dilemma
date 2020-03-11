#define CATCH_CONFIG_MAIN
#include <vector>
#include <cstddef>
#include <memory>
#include "Test.hpp"
#include "Decision.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
using namespace PrisonersDilemma;

void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const std::unique_ptr<Strategy> & strategy
);

void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const std::unique_ptr<Strategy> & strategy
)
{
	check( strategyDecisions.size() == partnerDecisions.size() );
	std::vector<Decision> strategyCummulativeDecisions, partnerCummulativeDecisions;
	{
		check( strategy->makeInitialDecision() == strategyDecisions.at(0) );
		strategyCummulativeDecisions.push_back(strategyDecisions.at(0));
		partnerCummulativeDecisions.push_back(partnerDecisions.at(0));
	}
	for (size_t turn=1 ; turn<strategyDecisions.size() ; ++turn)
	{
		check( strategy->makeDecision(partnerDecisions.at(turn-1)) == strategyDecisions.at(turn) );
		strategyCummulativeDecisions.push_back(strategyDecisions.at(turn));
		partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
	}
	return;
}
