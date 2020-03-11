#include <vector>
#include "Test.hpp"
#include "Decision.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
using namespace PrisonersDilemma;

const std::vector<Decision> emptyDecisions   = {};
const std::vector<Decision> startCooperating = {Decision::cooperate};
const std::vector<Decision> startDefecting   = {Decision::defect   };

extern void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const std::unique_ptr<Strategy> & strategy
);

TestCase("Always Cooperate", "[Strategies]")
{
	auto allC = AlwaysCooperate::creator()();
	require( allC->name        == "Always Cooperate"  );
	require( allC->shortName   == "AllC"              );
	require( allC->description == "Always cooperate." );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
		},
		allC
	);
	return;
}
