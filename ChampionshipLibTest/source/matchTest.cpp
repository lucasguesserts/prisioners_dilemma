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
	return;
}
