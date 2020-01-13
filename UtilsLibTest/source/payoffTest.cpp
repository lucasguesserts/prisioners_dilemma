#include <Test.hpp>
#include <Payoff.hpp>

TestCase("Payoff order", "[Payoff]")
{
	check( Payoff::suckers    >  Payoff::punishment );
	check( Payoff::punishment >  Payoff::reward );
	check( Payoff::reward     >  Payoff::temptation );

	check( 2*static_cast<int>(Payoff::reward)   >= static_cast<int>(Payoff::temptation) + static_cast<int>(Payoff::punishment) );
	return;
}

TestCase("Payoff sum", "[Payoff]")
{
	check( Payoff::reward  + Payoff::punishment == 3u );
	check( Payoff::suckers + 2u                 == 5u );
	check( 2u              + Payoff::temptation == 2u );
	return;
}

TestCase("Payoff left", "[PayoffComputer]")
{
	check( PayoffComputer::left(Decision::cooperate, Decision::cooperate) == Payoff::reward     );
	check( PayoffComputer::left(Decision::cooperate, Decision::defect   ) == Payoff::suckers    );
	check( PayoffComputer::left(Decision::defect   , Decision::cooperate) == Payoff::temptation );
	check( PayoffComputer::left(Decision::defect   , Decision::defect   ) == Payoff::punishment );
	return;
}

TestCase("Payoff right", "[PayoffComputer]")
{
	check( PayoffComputer::right(Decision::cooperate, Decision::cooperate) == Payoff::reward     );
	check( PayoffComputer::right(Decision::cooperate, Decision::defect   ) == Payoff::temptation );
	check( PayoffComputer::right(Decision::defect   , Decision::cooperate) == Payoff::suckers    );
	check( PayoffComputer::right(Decision::defect   , Decision::defect   ) == Payoff::punishment );
	return;
}
