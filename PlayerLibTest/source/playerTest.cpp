#include <Test.hpp>
#include <Strategies.hpp>
#include <Player.hpp>

TestCase("Always cooperate player", "[Player]")
{
	Player alwaysCooperate(allC);
	check( alwaysCooperate.strategy == &allC );
	return;
}
