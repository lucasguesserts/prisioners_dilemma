// TODO: define a way of retrieving the player data
// TODO: remove the define directive below
#define private public

#include <vector>
#include "Test.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
using namespace PrisonersDilemma;

TestCase("Always cooperate player", "[Player]")
{
	const Player alwaysCooperate(0u, AlwaysCooperate::creator());
	auto allC = alwaysCooperate.getStrategy();
	require( allC->name        == "Always Cooperate"  );
	require( allC->shortName   == "AllC"              );
	require( allC->description == "Always cooperate." );
	return;
}

TestCase("Save match", "[Player]")
{
	Player alwaysCooperate(0u, AlwaysCooperate::creator());
	const std::vector<Decision> decisions = {Decision::cooperate, Decision::cooperate};
	const std::vector<Payoff>   payoff    = {Payoff::reward, Payoff::reward};
	const Identifier            partner   = 5u;

	alwaysCooperate.saveMatch(decisions, payoff, partner);
	alwaysCooperate.saveMatch(decisions, payoff, partner);

	check( alwaysCooperate.decisions == std::vector<std::vector<Decision>> {decisions, decisions} );
	check( alwaysCooperate.payoff    == std::vector<std::vector<Payoff>>   {payoff,    payoff   } );
	check( alwaysCooperate.partners  == std::vector<Identifier>            {partner,   partner  } );
	return;
}

TestCase("Player score", "[Player]")
{
	const Identifier partnerId = 5u;
	Player alwaysCooperate(0u, AlwaysCooperate::creator());
	alwaysCooperate.saveMatch(
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::reward,      Payoff::suckers,     Payoff::reward },
		partnerId
	);
	alwaysCooperate.saveMatch(
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::suckers,     Payoff::reward,      Payoff::suckers     },
		partnerId
	);
	check(alwaysCooperate.score() == 12u );
	return;
}
