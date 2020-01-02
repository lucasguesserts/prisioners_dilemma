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

TestCase("Pavlov", "[Strategies]")
{
	std::vector<Decision> pavlovDecisions, partnerDecisions;
	section("metadata")
	{
		check( pvl.name ==      "Pavlov" );
		check( pvl.shortName == "PVL"    );
	}
	section("initial decision")
	{
		pavlovDecisions  = {};
		partnerDecisions = {};
		check( pvl.makeDecision(pavlovDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("reward received")
	{
		pavlovDecisions  = {Decision::cooperate};
		partnerDecisions = {Decision::cooperate};
		check( pvl.makeDecision(pavlovDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("suckers received")
	{
		pavlovDecisions  = {Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   };
		check( pvl.makeDecision(pavlovDecisions, partnerDecisions) == Decision::defect    );
	}
	section("punishment received")
	{
		pavlovDecisions  = {Decision::cooperate, Decision::cooperate, Decision::defect};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::defect};
		check( pvl.makeDecision(pavlovDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("temptation received")
	{
		pavlovDecisions  = {Decision::cooperate, Decision::cooperate, Decision::defect, Decision::cooperate, Decision::defect   };
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::defect, Decision::defect   , Decision::cooperate};
		check( pvl.makeDecision(pavlovDecisions, partnerDecisions) == Decision::defect    );
	}
	return;
}

TestCase("Tit for two tats", "[Strategies]")
{
	std::vector<Decision> tfttDecisions, partnerDecisions;
	section("metadata")
	{
		check( tftt.name ==      "Tit for Two Tats" );
		check( tftt.shortName == "TFTT"    );
	}
	section("initial decisions")
	{
		check( tftt.makeDecision({}, {}) == Decision::cooperate );
		check( tftt.makeDecision({Decision::cooperate}, {Decision::cooperate}) == Decision::cooperate );
		check( tftt.makeDecision({Decision::cooperate}, {Decision::defect   }) == Decision::cooperate );
	}
	section("cooperating 1")
	{
		tfttDecisions = {Decision::cooperate, Decision::cooperate, Decision::defect};
		partnerDecisions = {Decision::defect, Decision::defect , Decision::cooperate};
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("cooperating 2")
	{
		tfttDecisions = {Decision::cooperate, Decision::cooperate, Decision::defect, Decision::cooperate};
		partnerDecisions = {Decision::defect, Decision::defect , Decision::cooperate, Decision::defect};
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("defecting")
	{
		tfttDecisions = {Decision::cooperate, Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate , Decision::defect, Decision::defect};
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::defect );
	}
	return;
}
