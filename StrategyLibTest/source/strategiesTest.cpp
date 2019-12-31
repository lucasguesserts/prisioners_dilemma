#include <Test.hpp>
#include <Strategies.hpp>

std::vector<Decision> emptyDecisions = {};
std::vector<Decision> startCooperating = {Decision::cooperate};
std::vector<Decision> startDefecting = {Decision::defect};

TestCase("Always cooperate", "[Strategies]")
{
	check( alwaysCooperate.name      == "Always Cooperate" );
	check( alwaysCooperate.shortName == "AllC" );

	check( alwaysCooperate.makeDecision(emptyDecisions,   emptyDecisions) == Decision::cooperate );
	check( alwaysCooperate.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
	check( alwaysCooperate.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
	return;
}

TestCase("Always defect", "[Strategies]")
{
	check( alwaysDefect.name      == "Always Defect" );
	check( alwaysDefect.shortName == "AllD" );

	check( alwaysDefect.makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::defect );
	check( alwaysDefect.makeDecision(startCooperating, startDefecting  ) == Decision::defect );
	check( alwaysDefect.makeDecision(startDefecting,   startCooperating) == Decision::defect );
	return;
}
