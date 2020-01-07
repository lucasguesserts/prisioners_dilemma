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
		check( tftt.makeDecision({}, {})                                       == Decision::cooperate );
		check( tftt.makeDecision({Decision::cooperate}, {Decision::cooperate}) == Decision::cooperate );
		check( tftt.makeDecision({Decision::cooperate}, {Decision::defect   }) == Decision::cooperate );
	}
	section("cooperating 1")
	{
		tfttDecisions    = {Decision::cooperate, Decision::cooperate, Decision::defect   };
		partnerDecisions = {Decision::defect   , Decision::defect   , Decision::cooperate};
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("cooperating 2")
	{
		tfttDecisions    = {Decision::cooperate, Decision::cooperate, Decision::defect   , Decision::cooperate};
		partnerDecisions = {Decision::defect   , Decision::defect   , Decision::cooperate, Decision::defect   };
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("defecting")
	{
		tfttDecisions    = {Decision::cooperate, Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::defect   };
		check( tftt.makeDecision(tfttDecisions, partnerDecisions) == Decision::defect );
	}
	return;
}

TestCase("Gradual", "[Strategies]")
{
	section("metadata")
	{
		check( gradualS.name ==      "Gradual Strategy" );
		check( gradualS.shortName == "GradualS"    );
	}
	section("initial decisions")
	{
		check( gradualS.makeDecision({}, {})                                       == Decision::cooperate );
		check( gradualS.makeDecision({Decision::cooperate}, {Decision::cooperate}) == Decision::cooperate );
		check( gradualS.makeDecision({Decision::cooperate}, {Decision::defect   }) == Decision::defect );
	}
	section("gradually defecting")
	{
		std::vector<Decision> gradualSDecisions{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate
		};
		std::vector<Decision> partnerDecisions{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate
		};
		auto triggles = GradualS::findTriggles(partnerDecisions);
		section("find trigges")
		{
			check( triggles == std::vector<std::tuple<unsigned,unsigned>>{{1u,1u}, {6u,3u}} );
		}
		section("time to defect")
		{
			check     ( GradualS::timeToDefect(2 , triggles) );
			check     ( GradualS::timeToDefect(7 , triggles) );
			check     ( GradualS::timeToDefect(8 , triggles) );
			check     ( GradualS::timeToDefect(9 , triggles) );
			checkFalse( GradualS::timeToDefect(0 , triggles) );
			checkFalse( GradualS::timeToDefect(1 , triggles) );
			checkFalse( GradualS::timeToDefect(3 , triggles) );
			checkFalse( GradualS::timeToDefect(4 , triggles) );
			checkFalse( GradualS::timeToDefect(5 , triggles) );
			checkFalse( GradualS::timeToDefect(6 , triggles) );
			checkFalse( GradualS::timeToDefect(10, triggles) );
			checkFalse( GradualS::timeToDefect(11, triggles) );
		}
		std::vector<Decision> gradualSCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<gradualSDecisions.size() ; ++turn)
		{
			check( gradualS.makeDecision(gradualSCummulativeDecisions, partnerCummulativeDecisions) == gradualSDecisions.at(turn) );
			gradualSCummulativeDecisions.push_back(gradualSDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}

TestCase("Soft majority", "[Strategies]")
{
	std::vector<Decision> smDecisions, partnerDecisions;
	section("metadata")
	{
		check( sm.name == "Soft Majority" );
		check( sm.shortName == "SM" );
	}
	section("Initial move")
	{
		check( sm.makeDecision({}, {}) == Decision::cooperate );
	}
	section("majority cooperation")
	{
		smDecisions      = {Decision::cooperate, Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::cooperate, Decision::defect   };
		check( sm.makeDecision(smDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("equals cooperate and defect")
	{
		smDecisions      = {Decision::cooperate, Decision::cooperate, Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::cooperate, Decision::defect   };
		check( sm.makeDecision(smDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("majority defection")
	{
		smDecisions      = {Decision::cooperate, Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::defect   };
		check( sm.makeDecision(smDecisions, partnerDecisions) == Decision::defect );
	}
}

TestCase("Hard majority", "[Strategies]")
{
	std::vector<Decision> hmDecisions, partnerDecisions;
	section("metadata")
	{
		check( hm.name == "Hard Majority" );
		check( hm.shortName == "HM" );
	}
	section("Initial move")
	{
		check( hm.makeDecision({}, {}) == Decision::defect );
	}
	section("majority cooperation")
	{
		hmDecisions      = {Decision::defect   , Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::cooperate, Decision::defect   };
		check( hm.makeDecision(hmDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("equals cooperate and defect")
	{
		hmDecisions      = {Decision::defect   , Decision::cooperate, Decision::defect   , Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::cooperate, Decision::defect   };
		check( hm.makeDecision(hmDecisions, partnerDecisions) == Decision::defect );
	}
	section("majority defection")
	{
		hmDecisions      = {Decision::defect   , Decision::cooperate, Decision::defect};
		partnerDecisions = {Decision::cooperate, Decision::defect   , Decision::defect};
		check( hm.makeDecision(hmDecisions, partnerDecisions) == Decision::defect );
	}
}

TestCase("Naive prober", "[Strategies]")
{
	std::vector<Decision> npDecisions, partnerDecisions;
	section("metadata")
	{
		check( np.name ==      "Naive Prober" );
		check( np.shortName == "NP"           );
	}
	section("initial decisions")
	{
		checkDiscreteProbability(Decision::cooperate, 0.90, [&](){return np.makeDecision({},{});});
		checkDiscreteProbability(Decision::defect   , 0.10, [&](){return np.makeDecision({},{});});
	}
	section("tit for tat cooperate")
	{
		npDecisions      = {Decision::defect   , Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::cooperate};
		checkDiscreteProbability(Decision::cooperate, 0.90, [&](){return np.makeDecision(npDecisions, partnerDecisions);});
		checkDiscreteProbability(Decision::defect   , 0.10, [&](){return np.makeDecision(npDecisions, partnerDecisions);});
	}
	section("tit for tat defect")
	{
		npDecisions      = {Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   };
		check( np.makeDecision(npDecisions, partnerDecisions) == Decision::defect );
	}
	return;
}
