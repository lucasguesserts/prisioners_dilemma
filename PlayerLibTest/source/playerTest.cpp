#include <Test.hpp>
#include <Strategies.hpp>
#include <Player.hpp>

TestCase("Always cooperate player", "[Player]")
{
	Player alwaysCooperate(allC);
	check( alwaysCooperate.strategy == &allC );
	return;
}

TestCase("Save match", "[Player]")
{
	Player                alwaysCooperate(allC);
	std::vector<Decision> decisions = {Decision::cooperate, Decision::cooperate};
	std::vector<Payoff>   payoff    = {Payoff::reward, Payoff::reward};
	Strategy              *partner  = &allC;

	alwaysCooperate.saveMatch(decisions, payoff, partner);
	alwaysCooperate.saveMatch(decisions, payoff, partner);

	check( alwaysCooperate.decisions == std::vector<std::vector<Decision>> {decisions, decisions} );
	check( alwaysCooperate.payoff    == std::vector<std::vector<Payoff>>   {payoff,    payoff   } );
	check( alwaysCooperate.partners  == std::vector<Strategy*>             {partner,   partner  } );
	return;
}
