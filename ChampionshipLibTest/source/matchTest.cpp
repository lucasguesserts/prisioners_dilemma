#include <Test.hpp>
#include <Strategies.hpp>
#include <Match.hpp>

TestCase("Simple Match", "[Match]")
{
	Player alwaysCooperate(allC), alwaysDefect(allD);
	Match::match(alwaysCooperate, alwaysDefect);
	return;
}
