#include <vector>
#include "Test.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
using namespace PrisonersDilemma;

TestCase("Always cooperate player", "[Player]")
{
	const Player alwaysCooperate(allC);
	check( alwaysCooperate.strategy == &allC );
	return;
}

TestCase("Save match", "[Player]")
{
	Player alwaysCooperate(allC);
	const std::vector<Decision> decisions = {Decision::cooperate, Decision::cooperate};
	const std::vector<Payoff>   payoff    = {Payoff::reward, Payoff::reward};
	const Strategy * const      partner   = &allC;

	alwaysCooperate.saveMatch(decisions, payoff, partner);
	alwaysCooperate.saveMatch(decisions, payoff, partner);

	check( alwaysCooperate.decisions == std::vector<std::vector<Decision>> {decisions, decisions} );
	check( alwaysCooperate.payoff    == std::vector<std::vector<Payoff>>   {payoff,    payoff   } );
	check( alwaysCooperate.partners  == std::vector<const Strategy*>       {partner,   partner  } );
	return;
}

TestCase("Player score", "[Player]")
{
	Player alwaysCooperate(allC);
	alwaysCooperate.saveMatch(
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::reward,      Payoff::suckers,     Payoff::reward },
		&moon
	);
	alwaysCooperate.saveMatch(
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::suckers,     Payoff::reward,      Payoff::suckers     },
		&moon
	);
	check(alwaysCooperate.score() == 12u );
	return;
}
