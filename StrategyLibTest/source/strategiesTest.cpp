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

TestCase("Adaptative Tit For Tat", "[Strategies]")
{
	require( atft.name == "Adaptative Tit For Tat" );
	require( atft.shortName == "ATFT"              );
	checkDecisionHistory( // against tit fo tat
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		atft
	);
	checkDecisionHistory( // against suspicious tit fo tat
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
		},
		{
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		},
		atft
	);
	checkDecisionHistory( // against CCD behavior
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
		},
		{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
		},
		atft
	);
	checkDecisionHistory( // against CDD behavior
		{
			Decision::cooperate, // world = 0.50
			Decision::cooperate, // world = 0.60
			Decision::defect   , // world = 0.48
			Decision::defect   , // world = 0.38
			Decision::cooperate, // world = 0.51
			Decision::defect   , // world = 0.45
			Decision::defect   , // world = 0.32
			Decision::defect   , // world = 0.46
			Decision::defect   , // world = 0.36
		},
		{
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
		},
		atft
	);
	return;
}

TestCase("Meta-Regulated Adaptative Tit For Tat", "[Strategies]")
{
	require( mratft.name == "Meta-Regulated Adaptative Tit For Tat" );
	require( mratft.shortName == "MRATFT"              );
	// w: world
	// rc: adaptationRateCooperation
	// rd: adaptationRateDefection
	// n: thresholdCount
	// t: turn
	// td: thisDecision.back()
	// pd: partnerDecision.back()
	// adaptationWindow = 10
	// adaptationThreshold = 2
	// adaptationRateMinimum = 0.1
	// adaptationRateMaximim = 0.3
	//checkDecisionHistory( // against suspicious tit fo tat
	//	{
	//		                     //    w    rc    rd   n    t  td  pd
	//		Decision::cooperate, // 0.50 : 0.2 : 0.2 : 0 :  0 : C : D
	//		Decision::defect   , // 0.40 : 0.2 : 0.2 : 0 :  1 : D : C
	//		Decision::cooperate, // 0.52 : 0.2 : 0.2 : 0 :  2 : C : D
	//		Decision::defect   , // 0.42 : 0.2 : 0.2 : 0 :  3 : D : C
	//		Decision::cooperate, // 0.53 : 0.2 : 0.2 : 0 :  4 : C : D
	//		Decision::defect   , // 0.43 : 0.2 : 0.2 : 0 :  5 : D : C
	//		Decision::cooperate, // 0.54 : 0.2 : 0.2 : 0 :  6 : C : D
	//		Decision::defect   , // 0.43 : 0.2 : 0.2 : 0 :  7 : D : C
	//		Decision::cooperate, // 0.55 : 0.2 : 0.2 : 0 :  8 : C : D
	//		Decision::defect   , // 0.44 : 0.2 : 0.2 : 0 :  9 : D : C
	//		Decision::cooperate, // 0.61 : 0.3 : 0.1 : 0 : 10 : C : D
	//		Decision::cooperate, // 0.55 : 0.3 : 0.1 : 0 : 11 : C : C
	//		Decision::cooperate, // 0.68 : 0.3 : 0.1 : 1 : 12 : C : C
	//		Decision::cooperate, // 0.78 : 0.3 : 0.1 : 2 : 13 : C : C
	//		Decision::cooperate, // 0.84 : 0.3 : 0.1 : 3 : 14 : C : C
	//	},
	//	{
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//	},
	//	mratft
	//);
	checkDecisionHistory( // against CCD
		{
			                     //    w     rc     rd   n    t  td  pd
			Decision::cooperate, // 0.50 : 0.20 : 0.20 : 0 :  0 : C : C
			Decision::cooperate, // 0.60 : 0.20 : 0.20 : 1 :  1 : C : C
			Decision::cooperate, // 0.68 : 0.20 : 0.20 : 2 :  2 : C : D
			Decision::cooperate, // 0.54 : 0.20 : 0.20 : 2 :  3 : C : C
			Decision::cooperate, // 0.64 : 0.20 : 0.20 : 3 :  4 : C : C
			Decision::cooperate, // 0.71 : 0.20 : 0.20 : 4 :  5 : C : D
			Decision::cooperate, // 0.57 : 0.20 : 0.20 : 4 :  6 : C : C
			Decision::cooperate, // 0.65 : 0.20 : 0.20 : 5 :  7 : C : C
			Decision::cooperate, // 0.72 : 0.20 : 0.20 : 6 :  8 : C : D
			Decision::cooperate, // 0.58 : 0.20 : 0.20 : 6 :  9 : C : C
			Decision::cooperate, // 0.62 : 0.10 : 0.30 : 1 : 10 : C : C
			Decision::cooperate, // 0.66 : 0.10 : 0.30 : 2 : 11 : C : D
			Decision::defect   , // 0.46 : 0.10 : 0.30 : 2 : 12 : D : C
			Decision::cooperate, // 0.51 : 0.10 : 0.30 : 2 : 13 : C : C
			Decision::cooperate, // 0.56 : 0.10 : 0.30 : 3 : 14 : C : D
			Decision::defect   , // 0.39 : 0.10 : 0.30 : 3 : 15 : D : C
			Decision::defect   , // 0.45 : 0.10 : 0.30 : 3 : 16 : D : C
			Decision::cooperate, // 0.51 : 0.10 : 0.30 : 3 : 17 : C : D
			Decision::defect   , // 0.36 : 0.10 : 0.30 : 3 : 18 : D : C
			Decision::defect   , // 0.42 : 0.10 : 0.30 : 0 : 19 : D : C
			Decision::defect   , // 0.48 : 0.10 : 0.30 : 0 : 20 : D : D
			Decision::defect   , // 0.34 : 0.10 : 0.30 : 1 : 21 : D : C
			Decision::defect   , // 0.40 : 0.10 : 0.30 : 1 : 22 : D : C
		},
		{   // CCD strategy
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate, 
			Decision::cooperate,
		},
		mratft
	);
	return;
}
