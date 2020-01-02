#include <Test.hpp>
#include <Strategies.hpp>

std::vector<Decision> emptyDecisions = {};
std::vector<Decision> startCooperating = {Decision::cooperate};
std::vector<Decision> startDefecting = {Decision::defect};

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

TestCase("Tit for tat", "[Strategies]")
{
	section("metadata")
	{
		check( tft.name        == "Tit for Tat" );
		check( tft.shortName   == "TFT" );
		check( tft.description == "Start cooperating. Copy opponent's last move afterwards." );
	}
	section("Basic decisions")
	{
		check( tft.makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::cooperate );
		check( tft.makeDecision(startCooperating, startDefecting  ) == Decision::defect );
		check( tft.makeDecision(startCooperating, startCooperating) == Decision::cooperate );
	}
	section("Complex decisions")
	{
		std::vector<Decision> tftPartner   = {Decision::defect   , Decision::cooperate, Decision::cooperate};
		std::vector<Decision> tftDecisions = {Decision::cooperate, Decision::defect   , Decision::cooperate};
		check( tft.makeDecision(tftDecisions, tftPartner ) == Decision::cooperate );
	}
	return;
}

TestCase("Random", "[Strategies]")
{
	for(auto i=0 ; i<20 ; ++i)
	{
		auto decision = randS.makeDecision(emptyDecisions, emptyDecisions);
		check( ((decision==Decision::cooperate) || (decision==Decision::defect)) );
	}
	return;
}

TestCase("Grim Trigger", "[Strategies]")
{
	section("metadata")
	{
		check( grim.name        == "Grim Trigger" );
		check( grim.shortName   == "Grim"         );
	}
	section("Basic decisions")
	{
		check( grim.makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::cooperate );
		check( grim.makeDecision(startCooperating, startDefecting  ) == Decision::defect    );
		check( grim.makeDecision(startCooperating, startCooperating) == Decision::cooperate );
	}
	section("Complex decisions")
	{
		std::vector<Decision> partnerOfGrimDecisions   = {Decision::defect   , Decision::cooperate, Decision::cooperate};
		std::vector<Decision> grimDecisions            = {Decision::cooperate, Decision::defect   , Decision::defect   };
		check( grim.makeDecision(grimDecisions, partnerOfGrimDecisions ) == Decision::defect );
	}
	return;
}
