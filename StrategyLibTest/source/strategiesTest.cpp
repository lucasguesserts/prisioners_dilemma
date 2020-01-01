#include <Test.hpp>
#include <Strategies.hpp>

std::vector<Decision> emptyDecisions = {};
std::vector<Decision> startCooperating = {Decision::cooperate};
std::vector<Decision> startDefecting = {Decision::defect};

TestCase("Always cooperate", "[Strategies]")
{
	check( allC.name        == "Always Cooperate" );
	check( allC.shortName   == "AllC" );
	check( allC.description == "Always cooperate." );

	check( allC.makeDecision(emptyDecisions,   emptyDecisions) == Decision::cooperate );
	check( allC.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
	check( allC.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
	return;
}

TestCase("Always defect", "[Strategies]")
{
	check( allD.name        == "Always Defect" );
	check( allD.shortName   == "AllD" );
	check( allD.description == "Always defect." );

	check( allD.makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::defect );
	check( allD.makeDecision(startCooperating, startDefecting  ) == Decision::defect );
	check( allD.makeDecision(startDefecting,   startCooperating) == Decision::defect );
	return;
}

TestCase("Polimorphism", "[Strategy]")
{
	Strategy * strategy = &allD;
	check( strategy->name        == "Always Defect" );
	check( strategy->shortName   == "AllD" );
	check( strategy->description == "Always defect." );

	check( strategy->makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::defect );
	check( strategy->makeDecision(startCooperating, startDefecting  ) == Decision::defect );
	check( strategy->makeDecision(startDefecting,   startCooperating) == Decision::defect );
	return;
}
