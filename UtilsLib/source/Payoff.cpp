#include <stdexcept>
#include <tuple>
#include <Decision.hpp>
#include <Payoff.hpp>

unsigned operator+(const Payoff& lhs, const Payoff& rhs)
{
	return static_cast<unsigned>(lhs) + static_cast<unsigned>(rhs);
}

unsigned operator+(const Payoff& lhs, const unsigned& rhs)
{
	return static_cast<unsigned>(lhs) + rhs;
}

unsigned operator+(const unsigned& lhs, const Payoff& rhs)
{
	return lhs + static_cast<unsigned>(rhs);
}

std::tuple<Payoff, Payoff> PayoffComputer::compute(Decision leftDecision, Decision rightDecision)
{
	std::tuple<Payoff, Payoff> payoff;
	if      ((leftDecision==Decision::cooperate) && (rightDecision==Decision::cooperate))
		payoff = {Payoff::reward, Payoff::reward};
	else if ((leftDecision==Decision::cooperate) && (rightDecision==Decision::defect))
		payoff = {Payoff::suckers, Payoff::temptation};
	else if ((leftDecision==Decision::defect)    && (rightDecision==Decision::cooperate))
		payoff = {Payoff::temptation, Payoff::suckers};
	else if ((leftDecision==Decision::defect)    && (rightDecision==Decision::defect))
		payoff = {Payoff::punishment, Payoff::punishment};
	else
		throw std::logic_error("Decisions made by players are invalid!");
	return payoff;
}

Payoff PayoffComputer::left(Decision leftDecision, Decision rightDecision)
{
	return std::get<0>(PayoffComputer::compute(leftDecision, rightDecision));
}

Payoff PayoffComputer::right(Decision leftDecision, Decision rightDecision)
{
	return std::get<1>(PayoffComputer::compute(leftDecision, rightDecision));
}
