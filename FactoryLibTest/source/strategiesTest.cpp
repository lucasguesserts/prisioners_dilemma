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

TestCase("Always Defect", "[Strategies]")
{
	auto allD = AlwaysDefect::creator()();
	require( allD->name        == "Always Defect"  );
	require( allD->shortName   == "AllD"           );
	require( allD->description == "Always defect." );
	checkDecisionHistory(
		{
			Decision::defect,
			Decision::defect,
			Decision::defect,
			Decision::defect,
		},
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
		},
		allD
	);
	return;
}

TestCase("Tit For Tat", "[Strategies]")
{
	auto tft = TitForTat::creator()();
	require( tft->name        == "Tit For Tat"  );
	require( tft->shortName   == "TFT"          );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
		},
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
		},
		tft
	);
	return;
}

TestCase("Naive Prober", "[Strategies]")
{
	const double probabilityOfDefection = 0.15;
	auto np = NaiveProber::creator(probabilityOfDefection)();
	require( np->name      == "Naive Prober" );
	require( np->shortName == "NP"           );
	section("initial decisions")
	{
		checkDiscreteProbability(Decision::cooperate, 1.0 - probabilityOfDefection, [&](){return np->makeInitialDecision();});
		checkDiscreteProbability(Decision::defect   , probabilityOfDefection      , [&](){return np->makeInitialDecision();});
	}
	section("tit for tat cooperate")
	{
		checkDiscreteProbability(Decision::cooperate, 1.0 - probabilityOfDefection, [&](){return np->makeDecision(Decision::cooperate);});
		checkDiscreteProbability(Decision::defect   , probabilityOfDefection      , [&](){return np->makeDecision(Decision::cooperate);});
	}
	section("tit for tat defect")
	{
		check( np->makeDecision(Decision::defect) == Decision::defect );
	}
	return;
}
