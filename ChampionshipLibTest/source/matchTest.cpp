#include <vector>
#include "Test.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
#include "Match.hpp"

TestCase("Simple Match", "[Match]")
{
	Player alwaysCooperate(allC), alwaysDefect(allD);
	const unsigned numberOfTurns = 5;
	Match match(alwaysCooperate, alwaysDefect, numberOfTurns);
	section("Decisions")
	{
		const std::vector<Decision> leftDecisions (numberOfTurns, Decision::cooperate);
		const std::vector<Decision> rightDecisions(numberOfTurns, Decision::defect);
		check( match.leftDecisions  == leftDecisions  );
		check( match.rightDecisions == rightDecisions );
	}
	section("Payoff")
	{
		const std::vector<Payoff> leftPayoff (numberOfTurns, Payoff::suckers);
		const std::vector<Payoff> rightPayoff(numberOfTurns, Payoff::temptation);
		check( match.leftPayoff  == leftPayoff  );
		check( match.rightPayoff == rightPayoff );
	}
	section("left save match")
	{
		const std::vector<std::vector<Decision>> decisions = {std::vector<Decision>(numberOfTurns, Decision::cooperate)};
		const std::vector<std::vector<Payoff>>   payoff    = {std::vector<Payoff>  (numberOfTurns, Payoff::suckers)    };
		const std::vector<const Strategy *>      partners  = {&allD                                                    };
		check( alwaysCooperate.decisions == decisions );
		check( alwaysCooperate.payoff    == payoff    );
		check( alwaysCooperate.partners  == partners  );
	}
	section("right save match")
	{
		const std::vector<std::vector<Decision>> decisions = {std::vector<Decision>(numberOfTurns, Decision::defect)     };
		const std::vector<std::vector<Payoff>>   payoff    = {std::vector<Payoff>  (numberOfTurns, Payoff::temptation)   };
		const std::vector<const Strategy *>      partners  = {&allC                                                      };
		check( alwaysDefect.decisions == decisions );
		check( alwaysDefect.payoff    == payoff    );
		check( alwaysDefect.partners  == partners  );
	}
	return;
}

TestCase("Payer againd itself", "[Match]")
{
	Player alwaysCooperate(allC);
	const unsigned numberOfTurns = 5;
	Match match(alwaysCooperate, alwaysCooperate, numberOfTurns);
	section("save match")
	{
		const std::vector<std::vector<Decision>> decisions = {std::vector<Decision>(numberOfTurns, Decision::cooperate)};
		const std::vector<std::vector<Payoff>>   payoff    = {std::vector<Payoff>  (numberOfTurns, Payoff::reward)     };
		const std::vector<const Strategy *>      partners  = {&allC                                                    };
		check( alwaysCooperate.decisions == decisions );
		check( alwaysCooperate.payoff    == payoff    );
		check( alwaysCooperate.partners  == partners  );
	}
	return;
}
