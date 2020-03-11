#include "Test.hpp"
#include "Strategy.hpp"
#include <memory>
#include <vector>
#include <functional>
using namespace PrisonersDilemma;

extern void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const std::unique_ptr<Strategy> & strategy
);

class TestStrategy: public Strategy
{
	public:
		TestStrategy(void)
			: Strategy(
				{
					"Test Strategy",
					"TestS",
					"Class implemented just to make the following test case."
				}){}
		Decision makeInitialDecision(void) final override
		{
			return Decision::cooperate;
		}
		Decision makeDecision(const Decision & partnerLastDecision) final override
		{
			return partnerLastDecision;
		}
		static std::unique_ptr<Strategy> create(void)
		{
			return static_cast<std::unique_ptr<Strategy>>(std::make_unique<TestStrategy>());
		}
		static std::function<std::unique_ptr<Strategy>(void)> creator(void)
		{
			return [](){ return static_cast<std::unique_ptr<Strategy>>(std::make_unique<TestStrategy>()); };
		}
};

TestCase("strategy implementation", "[Strategy]")
{
	// auto strategyCreator = TestStrategy::creator();
	// auto strategy = strategyCreator();
	auto strategy = TestStrategy::create();
	section("description")
	{
		check( strategy->name        == "Test Strategy" );
		check( strategy->shortName   == "TestS" );
		check( strategy->description == "Class implemented just to make the following test case." );
	}
	section("initial decision")
	{
		check( strategy->makeInitialDecision() == Decision::cooperate );
	}
	section("decision history")
	{
		checkDecisionHistory(
			{
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::defect   ,
				Decision::cooperate,
			},
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::defect   ,
				Decision::cooperate,
				Decision::defect   ,
			},
			strategy
		);
	}
	return;
}
