#include <Test.hpp>
#include <Match.hpp>

TestCase("Simple Match", "[Match]")
{
	Player alwaysCooperate(allC), alwaysDefect(allD);
	Match match(alwaysCooperate, alwaysDefect);
	section("Decisions")
	{
		std::vector<Decision> leftDecisions (Match::numberOfTurns, Decision::cooperate);
		std::vector<Decision> rightDecisions(Match::numberOfTurns, Decision::defect);
		check( match.leftDecisions  == leftDecisions  );
		check( match.rightDecisions == rightDecisions );
	}
	section("Payoff")
	{
		std::vector<Payoff> leftPayoff (Match::numberOfTurns, Payoff::suckers);
		std::vector<Payoff> rightPayoff(Match::numberOfTurns, Payoff::temptation);
		check( match.leftPayoff  == leftPayoff  );
		check( match.rightPayoff == rightPayoff );
	}
	section("left save match")
	{
		std::vector<std::vector<Decision>> decisions = {std::vector<Decision>(Match::numberOfTurns, Decision::cooperate)};
		std::vector<std::vector<Payoff>>   payoff    = {std::vector<Payoff>  (Match::numberOfTurns, Payoff::suckers)    };
		std::vector<Strategy*>             partners  = {&allD                                                           };
		check( alwaysCooperate.decisions == decisions );
		check( alwaysCooperate.payoff    == payoff    );
		check( alwaysCooperate.partners  == partners  );
	}
	section("right save match")
	{
		std::vector<std::vector<Decision>> decisions = {std::vector<Decision>(Match::numberOfTurns, Decision::defect)     };
		std::vector<std::vector<Payoff>>   payoff    = {std::vector<Payoff>  (Match::numberOfTurns, Payoff::temptation)   };
		std::vector<Strategy*>             partners  = {&allC                                                             };
		check( alwaysDefect.decisions == decisions );
		check( alwaysDefect.payoff    == payoff    );
		check( alwaysDefect.partners  == partners  );
	}
	return;
}
