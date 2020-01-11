#include <Test.hpp>
#include <StrategyTest.hpp>
#include <Strategies.hpp>

std::vector<Decision> emptyDecisions = {};
std::vector<Decision> startCooperating = {Decision::cooperate};
std::vector<Decision> startDefecting   = {Decision::defect   };
std::vector<Decision> twoCooperations  = {Decision::cooperate, Decision::cooperate};
std::vector<Decision> twoDefections    = {Decision::defect,    Decision::defect   };

TestCase("Polimorphism", "[Strategy]")
{
	Strategy * strategy = &allD;
	require( strategy->name        == "Always Defect" );
	require( strategy->shortName   == "AllD" );
	require( strategy->description == "Always defect." );
	section("test decisions")
	{
		check( strategy->makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::defect );
		check( strategy->makeDecision(startCooperating, startDefecting  ) == Decision::defect );
		check( strategy->makeDecision(startDefecting,   startCooperating) == Decision::defect );
	}
	return;
}

TestCase("Always cooperate", "[Strategies]")
{
	require( allC.name        == "Always Cooperate" );
	require( allC.shortName   == "AllC" );
	require( allC.description == "Always cooperate." );
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

TestCase("Always defect", "[Strategies]")
{
	require( allD.name        == "Always Defect" );
	require( allD.shortName   == "AllD" );
	require( allD.description == "Always defect." );
	checkDecisionHistory(
		{
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
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

TestCase("Lunatic", "[Strategies]")
{
	require( moon.name        == "Lunatic" );
	require( moon.shortName   == "Moon"    );
	for(auto i=0 ; i<20 ; ++i)
	{
		auto decision = moon.makeDecision(emptyDecisions, emptyDecisions);
		check( ((decision==Decision::cooperate) || (decision==Decision::defect)) );
	}
	auto randomDecision = []{return moon.makeDecision(emptyDecisions, emptyDecisions);};
	checkDiscreteProbability(Decision::cooperate, 0.50, randomDecision);
	checkDiscreteProbability(Decision::defect   , 0.50, randomDecision);
	return;
}

TestCase("Grim Trigger", "[Strategies]")
{
	require( grim.name        == "Grim Trigger" );
	require( grim.shortName   == "Grim"         );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
		},
		grim
	);
	return;
}

TestCase("Pavlov", "[Strategies]")
{
	std::vector<Decision> pavlovDecisions, partnerDecisions;
	require( pvl.name ==      "Pavlov" );
	require( pvl.shortName == "PVL"    );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		},
		pvl
	);
	return;
}

TestCase("Gradual", "[Strategies]")
{
	require( gradualS.name ==      "Gradual Strategy" );
	require( gradualS.shortName == "GradualS"    );
	checkDecisionHistory(
		{
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
		},
		{
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
		},
		gradualS
	);
	return;
}

TestCase("Soft majority", "[Strategies]")
{
	std::vector<Decision> smDecisions, partnerDecisions;
	require( sm.name == "Soft Majority" );
	require( sm.shortName == "SM" );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate
		},
		sm
	);
}

TestCase("Hard majority", "[Strategies]")
{
	std::vector<Decision> hmDecisions, partnerDecisions;
	require( hm.name == "Hard Majority" );
	require( hm.shortName == "HM" );
	checkDecisionHistory(
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate
		},
		hm
	);
}

TestCase("Soft Grudger", "[Strategies]")
{
	require( sg.name      == "Soft Grudger" );
	require( sg.shortName == "SG"           );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate
		},
		sg
	);
	return;
}

TestCase("Prober", "[Strategies]")
{
	require( pb.name      == "Prober" );
	require( pb.shortName == "PB"     );
	section("initial decisions")
	{
		checkDecisionHistory(
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
			},
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::defect   ,
			},
			pb
		);
	}
	section("defection behavior")
	{
		checkDecisionHistory(
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::defect   ,
				Decision::defect   ,
			},
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
				Decision::defect   ,
			},
			pb
		);
	}
	section("tit for tat behavior 1")
	{
		checkDecisionHistory(
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
			},
			{
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
			},
			pb
		);
	}
	section("tit for tat behavior 2")
	{
		checkDecisionHistory(
			{
				Decision::defect   ,
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
				Decision::defect   ,
			},
			{
				Decision::cooperate,
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
				Decision::defect   ,
				Decision::cooperate,
			},
			pb
		);
	}
	return;
}

TestCase("Firm but Fair", "[Strategies]")
{
	require( fbf.name      == "Firm but Fair" );
	require( fbf.shortName == "FBF"           );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		fbf
	);
	// fbf decision, partner decision -> fbf payoff -> fbf next decision
	// cooperate, cooperate -> reward     -> cooperate
	// cooperate, defect    -> suckers    -> defect
	// defect   , cooperate -> temptation -> cooperate
	// cooperate, defect    -> suckers    -> defect
	// defect   , defect    -> punishment -> cooperate
	// cooperate, cooperate -> reward     -> cooperate
	return;
}

TestCase("Tit for tat", "[Strategies]")
{
	require( tft.name        == "Tit for Tat" );
	require( tft.shortName   == "TFT" );
	require( tft.description == "Start cooperating. Copy opponent's last move afterwards." );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		tft
	);
	return;
}

TestCase("Tit for two tats", "[Strategies]")
{
	std::vector<Decision> tfttDecisions, partnerDecisions;
	require( tftt.name ==      "Tit for Two Tats" );
	require( tftt.shortName == "TFTT"    );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
		},
		tftt
	);
	return;
}

TestCase("Two Tits for Tat", "[Strategies]")
{
	std::vector<Decision> ttftDecisions, partnerDecisions;
	require( ttft.name ==      "Two Tits for Tat" );
	require( ttft.shortName == "TTFT"             );
	checkDecisionHistory(
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		ttft
	);
	return;
}

TestCase("Naive prober", "[Strategies]")
{
	std::vector<Decision> npDecisions, partnerDecisions;
	require( np.name ==      "Naive Prober" );
	require( np.shortName == "NP"           );
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

TestCase("Remorseful Prober", "[Strategies]")
{
	std::vector<Decision> rpDecisions, partnerDecisions;
	require( rp.name      == "Remorseful Prober" );
	require( rp.shortName == "RP"                );
	section("initial decision")
	{
		check( rp.makeDecision(emptyDecisions, emptyDecisions) == Decision::cooperate );
	}
	section("cooperating only")
	{
		checkDiscreteProbability(Decision::defect   , 0.10, [&](){return rp.makeDecision(startCooperating, startCooperating);});
		checkDiscreteProbability(Decision::cooperate, 0.90, [&](){return rp.makeDecision(startCooperating, startCooperating);});
	}
	section("remorse because of probing behavior")
	{
		rpDecisions      = {Decision::cooperate, Decision::defect   , Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::cooperate, Decision::defect   };
		check( rp.makeDecision(rpDecisions, partnerDecisions) == Decision::cooperate );
	}
	section("answer to defections")
	{
		rpDecisions      = {Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   };
		check( rp.makeDecision(rpDecisions,    partnerDecisions) == Decision::defect);
		check( rp.makeDecision(startCooperating, startDefecting)   == Decision::defect );
	}
	return;
}

TestCase("Generous Tit for tat", "[Strategies]")
{
	require( gtft.name        == "Generous Tit for Tat" );
	require( gtft.shortName   == "GTFT" );
	section("initial decision")
	{
		check( gtft.makeDecision(emptyDecisions, emptyDecisions) == Decision::cooperate );
	}
	section("cooperation behavior")
	{
		auto randFunc = []{return gtft.makeDecision(startCooperating,startCooperating);};
		checkDiscreteProbability(Decision::cooperate, 1.0, randFunc);
	}
	section("defection behavior")
	{
		auto randFunc = []{return gtft.makeDecision(startCooperating,startDefecting  );};
		checkDiscreteProbability(Decision::cooperate, 0.1, randFunc);
		checkDiscreteProbability(Decision::defect   , 0.9, randFunc);
	}
	return;
}

TestCase("Suspisious Tit for Tat", "[Strategies]")
{
	require( stft.name        == "Suspicious Tit for Tat" );
	require( stft.shortName   == "STFT" );
	checkDecisionHistory(
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
		},
		stft
	);
	return;
}

TestCase("Hard Tit For Tat", "[Strategies]")
{
	require( htft.name      == "Hard Tit for Tat" );
	require( htft.shortName == "HTFT"             );
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
			Decision::defect   ,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		htft
	);
	return;
}

TestCase("Reverse Tit for tat", "[Strategies]")
{
	require( rtft.name        == "Reverse Tit for Tat" );
	require( rtft.shortName   == "RTFT" );
	checkDecisionHistory(
		{
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
		},
		rtft
	);
	return;
}
