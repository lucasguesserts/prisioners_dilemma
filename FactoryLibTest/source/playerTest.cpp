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
	const std::vector<PlayerData> matchHistory = {
		{ 5u, {Decision::cooperate, Decision::cooperate}, {Payoff::reward,     Payoff::reward} },
		{ 4u, {Decision::defect   , Decision::cooperate}, {Payoff::temptation, Payoff::reward} },
	};
	alwaysCooperate.saveMatch(matchHistory.at(0));
	alwaysCooperate.saveMatch(matchHistory.at(1));
	check( alwaysCooperate.getHistory() == matchHistory );
	return;
}

TestCase("Player score", "[Player]")
{
	const Identifier partnerId = 5u;
	Player alwaysCooperate(0u, AlwaysCooperate::creator());
	alwaysCooperate.saveMatch({
		partnerId,
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::reward,      Payoff::suckers,     Payoff::reward      }
	});
	alwaysCooperate.saveMatch({
		partnerId,
		{ Decision::cooperate, Decision::cooperate, Decision::cooperate },
		{ Payoff::suckers,     Payoff::reward,      Payoff::suckers     }
	});
	check(alwaysCooperate.getScore() == 12u );
	return;
}
