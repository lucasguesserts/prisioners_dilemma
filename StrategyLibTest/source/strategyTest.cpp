#include "Test.hpp"
#include "Strategy.hpp"
using namespace PrisonersDilemma;

extern void checkDecisionHistory(
	const std::vector<Decision> strategyDecisions,
	const std::vector<Decision> partnerDecisions,
	const Strategy & strategy
);

class TestStrategy: public Strategy
{
	public:
		TestStrategy(void)
			: Strategy(
					"Test Strategy",
					"TestS",
					"Class implemented just to make the following test case."){}
		Decision makeDecision(
			[[maybe_unused]] const std::vector<Decision>& thisDecision,
			[[maybe_unused]] const std::vector<Decision>& partnerDecision
		) const final override {
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

class TestHistoryStrategy: public Strategy
{
	public:
		TestHistoryStrategy(void)
			: Strategy(
					"Test History Strategy",
					"TestHS",
					"Class implemented just to make the diecicion history test case."){}
		Decision makeDecision(
			[[maybe_unused]] const std::vector<Decision>& thisDecision,
			[[maybe_unused]] const std::vector<Decision>& partnerDecision
		) const final override {
			Decision decision;
			if ( partnerDecision.empty() )
				decision = Decision::cooperate;
			else
				decision = !partnerDecision.back();
			return decision;
		}
};

TestCase("Decisions history", "[Strategy]")
{
	const TestHistoryStrategy strategy;
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
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
	return;
}
