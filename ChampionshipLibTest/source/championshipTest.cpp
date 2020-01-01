#include <Test.hpp>
#include <Strategies.hpp>
#include <Championship.hpp>

TestCase("Three players chapionship", "[Championship]")
{
	Championship championship({
		&allC,
		&allD,
		&tft
	});

	section("Championship constructor", "[Championship]")
	{
		check( championship.players[0].strategy == &allC );
		check( championship.players[1].strategy == &allD );
		check( championship.players[2].strategy == &tft );
	}

	section("Compete", "[Championship]")
	{
		championship.compete();
		section("Always cooperate")
		{
			std::vector<std::vector<Decision>> decisions(3, std::vector<Decision>{Match::numberOfTurns, Decision::cooperate});
			check(championship.players[0].decisions == decisions );
		}
	}

	return;
}
