#include <Test.hpp>
#include <iostream>
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
	section("test decisions")
	{
		check( allC.makeDecision(emptyDecisions,   emptyDecisions) == Decision::cooperate );
		check( allC.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
		check( allC.makeDecision(startCooperating, startDefecting) == Decision::cooperate );
	}
	return;
}

TestCase("Always defect", "[Strategies]")
{
	require( allD.name        == "Always Defect" );
	require( allD.shortName   == "AllD" );
	require( allD.description == "Always defect." );
	section("test decisions")
	{
		check( allD.makeDecision(emptyDecisions,   emptyDecisions  ) == Decision::defect );
		check( allD.makeDecision(startCooperating, startDefecting  ) == Decision::defect );
		check( allD.makeDecision(startDefecting,   startCooperating) == Decision::defect );
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
	require( pvl.name ==      "Pavlov" );
	require( pvl.shortName == "PVL"    );
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

TestCase("Gradual", "[Strategies]")
{
	require( gradualS.name ==      "Gradual Strategy" );
	require( gradualS.shortName == "GradualS"    );
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
	require( sm.name == "Soft Majority" );
	require( sm.shortName == "SM" );
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
	require( hm.name == "Hard Majority" );
	require( hm.shortName == "HM" );
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
		std::cout << "Start of Test!!!" << "\n\n\n";
		for (std::vector<Decision>::size_type turn=0 ; turn<htftDecisions.size() ; ++turn)
		{
			check( htft.makeDecision(htftCummulativeDecisions, partnerCummulativeDecisions) == htftDecisions.at(turn) );
			htftCummulativeDecisions.push_back(htftDecisions.at(turn));
			partnerCummulativeDecisions.push_back(partnerDecisions.at(turn));
		}
	}
	return;
}
