#include <vector>
#include "Test.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
#include "Match.hpp"
using namespace PrisonersDilemma;

TestCase("Simple Match", "[Match]")
{
	Player alwaysCooperate(0u, AlwaysCooperate::creator());
	Player alwaysDefect   (1u, AlwaysDefect::creator()   );
	const unsigned numberOfTurns = 5;
	Match match(alwaysCooperate, alwaysDefect, numberOfTurns);
	section("always cooperate")
	{
		const PlayerData correctPlayerData = {
			alwaysDefect.getIdentifier(),
			{numberOfTurns, Decision::cooperate},
			{numberOfTurns, Payoff::suckers    }
		};
		check( alwaysCooperate.getHistory().at(0)  == correctPlayerData );
	}
	section("always defect")
	{
		const PlayerData correctPlayerData = {
			alwaysCooperate.getIdentifier(),
			{numberOfTurns, Decision::defect  },
			{numberOfTurns, Payoff::temptation}
		};
		check( alwaysDefect.getHistory().at(0)  == correctPlayerData );
	}
	return;
}

TestCase("Player against itself", "[Match]")
{
	Player alwaysCooperate(0u, AlwaysCooperate::creator());
	const unsigned numberOfTurns = 5;
	Match match(alwaysCooperate, alwaysCooperate, numberOfTurns);
	const PlayerData correctPlayerData = {
		alwaysCooperate.getIdentifier(),
		{numberOfTurns, Decision::cooperate},
		{numberOfTurns, Payoff::reward     }
	};
	check( alwaysCooperate.getHistory().at(0)  == correctPlayerData );
	check( alwaysCooperate.getHistory().size() == 1                );
	return;
}
