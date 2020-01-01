#include <Test.hpp>
#include <Payoff.hpp>

//TestCase("Payoff computer", "[PayoffComputer]")
//{
//	check( PayoffComputer::compute(Decision::cooperate, Decision::cooperate) == std::make_tuple(Payoff::reward    , Payoff::reward    ) );
//	check( PayoffComputer::compute(Decision::cooperate, Decision::defect   ) == std::make_tuple(Payoff::suckers   , Payoff::temptation) );
//	check( PayoffComputer::compute(Decision::defect   , Decision::cooperate) == std::make_tuple(Payoff::temptation, Payoff::suckers   ) );
//	check( PayoffComputer::compute(Decision::defect   , Decision::defect   ) == std::make_tuple(Payoff::punishment, Payoff::punishment) );
//	return;
//}

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
