#include <Test.hpp>
#include <Payoff.hpp>

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
