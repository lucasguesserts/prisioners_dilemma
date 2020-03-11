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
		TestStrategy(const Decision & decision = Decision::cooperate)
			: Strategy(
				{
					"Test Strategy",
					"TestS",
					"Class implemented just to make the following test case."
				}),
			  decision(decision) {}
		Decision makeInitialDecision(void) final override
		{
			return this->decision;
		}
		Decision makeDecision([[maybe_unused]] const Decision & partnerLastDecision) final override
		{
			return this->decision;
		}
		// This method requires that there is a constructor which receives no
		// parameter: TestStrategy(void).
		// It was accomplished by defining a default value to the constructor.
		static std::unique_ptr<Strategy> create(void)
		{
			return static_cast<std::unique_ptr<Strategy>>(std::make_unique<TestStrategy>());
		}
		// The method receives the same parameters as the constructor does.
		// It might be annoying to always define this function as receiving
		// the same parameters, capturing it and then giving it to 'make_unique'.
		static std::function<std::unique_ptr<Strategy>(void)> creator(const Decision & decision)
		{
			return [&decision](){ return static_cast<std::unique_ptr<Strategy>>(std::make_unique<TestStrategy>(decision)); };
		}
	private:
		const Decision decision;

};

TestCase("strategy implementation", "[Strategy]")
{
	auto strategyCreate = TestStrategy::creator(Decision::cooperate);
	auto strategy = strategyCreate();
	// auto strategy = TestStrategy::create();
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
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
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
