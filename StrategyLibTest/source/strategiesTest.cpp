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

TestCase("Random", "[Strategies]")
{
	for(auto i=0 ; i<20 ; ++i)
	{
		auto decision = randS.makeDecision(emptyDecisions, emptyDecisions);
		check( ((decision==Decision::cooperate) || (decision==Decision::defect)) );
	}
	auto randomDecision = []{return randS.makeDecision(emptyDecisions, emptyDecisions);};
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

TestCase("Soft Grudger", "[Strategies]")
{
	require( sg.name      == "Soft Grudger" );
	require( sg.shortName == "SG"           );
	section("initial decision")
	{
		check( sg.makeDecision(emptyDecisions, emptyDecisions)     == Decision::cooperate );
	}
	section("cooperation")
	{
		check( sg.makeDecision(startCooperating, startCooperating) == Decision::cooperate);
		check( sg.makeDecision(twoCooperations, twoCooperations)   == Decision::cooperate);
	}
	section("reaction to defection")
	{
		std::vector<Decision> sgDecisions{
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
		};
		std::vector<Decision> partnerDecisions{
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
		};
		std::vector<Decision> sgCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<sgDecisions.size() ; ++turn)
		{
			check( sg.makeDecision(sgCummulativeDecisions, partnerCummulativeDecisions) == sgDecisions.at(turn) );
			sgCummulativeDecisions.push_back(sgDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}

TestCase("Prober", "[Strategies]")
{
	require( pb.name      == "Prober" );
	require( pb.shortName == "PB"     );
	section("initial decisions")
	{
		check( pb.makeDecision(emptyDecisions  , emptyDecisions  ) == Decision::defect    );
		check( pb.makeDecision(startCooperating, startCooperating) == Decision::cooperate );
		check( pb.makeDecision(twoCooperations , twoCooperations ) == Decision::cooperate );
	}
	section("defection behavior")
	{
		std::vector<Decision> pbDecisions{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
		};
		std::vector<Decision> partnerDecisions{
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		};
		std::vector<Decision> pbCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<pbDecisions.size() ; ++turn)
		{
			check( pb.makeDecision(pbCummulativeDecisions, partnerCummulativeDecisions) == pbDecisions.at(turn) );
			pbCummulativeDecisions.push_back(pbDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	section("tit for tat behavior 1")
	{
		std::vector<Decision> pbDecisions{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		};
		std::vector<Decision> partnerDecisions{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
		};
		std::vector<Decision> pbCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<pbDecisions.size() ; ++turn)
		{
			check( pb.makeDecision(pbCummulativeDecisions, partnerCummulativeDecisions) == pbDecisions.at(turn) );
			pbCummulativeDecisions.push_back(pbDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	section("tit for tat behavior 2")
	{
		std::vector<Decision> pbDecisions{
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		};
		std::vector<Decision> partnerDecisions{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
			Decision::cooperate,
		};
		std::vector<Decision> pbCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<pbDecisions.size() ; ++turn)
		{
			check( pb.makeDecision(pbCummulativeDecisions, partnerCummulativeDecisions) == pbDecisions.at(turn) );
			pbCummulativeDecisions.push_back(pbDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}

TestCase("Firm but Fair", "[Strategies]")
{
	require( fbf.name      == "Firm but Fair" );
	require( fbf.shortName == "FBF"           );
	section("initial decisions")
	{
		check( fbf.makeDecision(emptyDecisions  , emptyDecisions  ) == Decision::cooperate );
	}
	section("all cases")
	{
		std::vector<Decision> fbfDecisions{
			Decision::cooperate,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
		};
		std::vector<Decision> partnerDecisions{
			Decision::cooperate,
			Decision::defect   ,
			Decision::cooperate,
			Decision::defect   ,
			Decision::defect   ,
			Decision::cooperate,
		};
		// fbf decision, partner decision -> fbf payoff -> fbf next decision
		// cooperate, cooperate -> reward     -> cooperate
		// cooperate, defect    -> suckers    -> defect
		// defect   , cooperate -> temptation -> cooperate
		// cooperate, defect    -> suckers    -> defect
		// defect   , defect    -> punishment -> cooperate
		// cooperate, cooperate -> reward     -> cooperate
		std::vector<Decision> fbfCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<fbfDecisions.size() ; ++turn)
		{
			check( fbf.makeDecision(fbfCummulativeDecisions, partnerCummulativeDecisions) == fbfDecisions.at(turn) );
			fbfCummulativeDecisions.push_back(fbfDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}

TestCase("Tit for tat", "[Strategies]")
{
	require( tft.name        == "Tit for Tat" );
	require( tft.shortName   == "TFT" );
	require( tft.description == "Start cooperating. Copy opponent's last move afterwards." );
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

TestCase("Tit for two tats", "[Strategies]")
{
	std::vector<Decision> tfttDecisions, partnerDecisions;
	require( tftt.name ==      "Tit for Two Tats" );
	require( tftt.shortName == "TFTT"    );
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

TestCase("Two Tits for Tat", "[Strategies]")
{
	std::vector<Decision> ttftDecisions, partnerDecisions;
	require( ttft.name ==      "Two Tits for Tat" );
	require( ttft.shortName == "TTFT"             );
	section("initial decisions")
	{
		check( ttft.makeDecision({}, {})                                       == Decision::cooperate );
		check( ttft.makeDecision({Decision::cooperate}, {Decision::cooperate}) == Decision::cooperate );
		check( ttft.makeDecision({Decision::cooperate}, {Decision::defect   }) == Decision::defect    );
	}
	section("defecting 1")
	{
		ttftDecisions    = {Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::defect   };
		check( ttft.makeDecision(ttftDecisions, partnerDecisions) == Decision::defect    );
	}
	section("defecting 2")
	{
		ttftDecisions    = {Decision::cooperate, Decision::defect   };
		partnerDecisions = {Decision::defect   , Decision::cooperate};
		check( ttft.makeDecision(ttftDecisions, partnerDecisions) == Decision::defect    );
	}
	section("defecting 3")
	{
		ttftDecisions    = {Decision::cooperate, Decision::defect   };
		partnerDecisions = {Decision::defect   , Decision::defect   };
		check( ttft.makeDecision(ttftDecisions, partnerDecisions) == Decision::defect    );
	}
	section("cooperating")
	{
		ttftDecisions    = {Decision::cooperate, Decision::cooperate};
		partnerDecisions = {Decision::cooperate, Decision::cooperate};
		check( ttft.makeDecision(ttftDecisions, partnerDecisions) == Decision::cooperate );
	}
	return;
}

TestCase("Reverse Tit for tat", "[Strategies]")
{
	require( rtft.name        == "Reverse Tit for Tat" );
	require( rtft.shortName   == "RTFT" );
	section("Basic decisions")
	{
		check( rtft.makeDecision(emptyDecisions, emptyDecisions  ) == Decision::defect    );
		check( rtft.makeDecision(startDefecting, startDefecting  ) == Decision::cooperate );
		check( rtft.makeDecision(startDefecting, startCooperating) == Decision::defect    );
	}
	section("Complex decisions")
	{
		std::vector<Decision> rtftPartner   = {Decision::defect   , Decision::defect, Decision::cooperate};
		std::vector<Decision> rtftDecisions = {Decision::cooperate, Decision::defect, Decision::cooperate};
		check( rtft.makeDecision(rtftDecisions, rtftPartner ) == Decision::defect );
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
	section("Basic decisions")
	{
		check( stft.makeDecision(emptyDecisions, emptyDecisions  ) == Decision::defect    );
		check( stft.makeDecision(startDefecting, startDefecting  ) == Decision::defect    );
		check( stft.makeDecision(startDefecting, startCooperating) == Decision::cooperate );
	}
	section("Complex decisions")
	{
		check( stft.makeDecision(twoCooperations, twoCooperations ) == Decision::cooperate );
		check( stft.makeDecision(twoDefections  , twoDefections   ) == Decision::defect    );
	}
	return;
}

TestCase("Hard Tit For Tat", "[Strategies]")
{
	require( htft.name      == "Hard Tit for Tat" );
	require( htft.shortName == "HTFT"             );
	//checkDecisionHistory(
	//	{
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//	},
	//	{
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::defect   ,
	//		Decision::defect   ,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//		Decision::cooperate,
	//	},
	//	&htft
	//);
	section("initial decisions")
	{
		check( htft.makeDecision(emptyDecisions  , emptyDecisions  ) == Decision::cooperate );
	}
	section("all cases")
	{
		std::vector<Decision> htftDecisions{
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
		};
		std::vector<Decision> partnerDecisions{
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
		};
		std::vector<Decision> htftCummulativeDecisions, partnerCummulativeDecisions;
		for (std::vector<Decision>::size_type turn=0 ; turn<htftDecisions.size() ; ++turn)
		{
			check( htft.makeDecision(htftCummulativeDecisions, partnerCummulativeDecisions) == htftDecisions.at(turn) );
			htftCummulativeDecisions.push_back(htftDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}
