#include <Test.hpp>
#include <Strategy.hpp>

class TestStrategy: public Strategy
{
	public:
		TestStrategy(void)
			: Strategy(
					"Test Strategy",
					"TestS",
					"Class implemented just to make the following test case."){}
		Decision makeDecision(
			[[maybe_unused]] std::vector<Decision> thisDecision,
			[[maybe_unused]] std::vector<Decision> partnerDecision
		){
			return Decision::cooperate;
		}
};

TestCase("strategy implementation", "[Strategy]")
{
	TestStrategy strategy;
	check( strategy.name == "Test Strategy" );
	check( strategy.shortName == "TestS" );
	check( strategy.description == "Class implemented just to make the following test case." );
	check(
		strategy.makeDecision(
			std::vector<Decision>{Decision::cooperate},
			std::vector<Decision>{Decision::defect})
		== Decision::cooperate
	);
	return;
}
