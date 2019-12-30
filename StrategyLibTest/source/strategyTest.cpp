#include <Test.hpp>
#include <Strategy.hpp>

TestCase("strategy constructor", "[Strategy]")
{
	Strategy strategy;
	check( strategy.name == "" );
	check( strategy.description == "" );
	check( strategy.numberOfMatches == 0 );
	check( strategy.accumulatedPayoff == 0u );
	return;
}
