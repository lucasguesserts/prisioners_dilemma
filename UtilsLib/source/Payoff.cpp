#include <stdexcept>
#include <tuple>
#include "Decision.hpp"
#include "Payoff.hpp"
using namespace PrisonersDilemma;

unsigned PrisonersDilemma::operator+(const Payoff& lhs, const Payoff& rhs)
{
	return static_cast<unsigned>(lhs) + static_cast<unsigned>(rhs);
}

unsigned PrisonersDilemma::operator+(const Payoff& lhs, const unsigned& rhs)
{
	return static_cast<unsigned>(lhs) + rhs;
}

unsigned PrisonersDilemma::operator+(const unsigned& lhs, const Payoff& rhs)
{
	return lhs + static_cast<unsigned>(rhs);
}

std::tuple<Payoff, Payoff> PayoffComputer::compute(const Decision& leftDecision, const Decision& rightDecision)
{
	std::tuple<Payoff, Payoff> result;
	if      ((leftDecision==Decision::cooperate) && (rightDecision==Decision::cooperate))
		result = {Payoff::reward, Payoff::reward};
	else if ((leftDecision==Decision::cooperate) && (rightDecision==Decision::defect))
		result = {Payoff::suckers, Payoff::temptation};
	else if ((leftDecision==Decision::defect)    && (rightDecision==Decision::cooperate))
		result = {Payoff::temptation, Payoff::suckers};
	else if ((leftDecision==Decision::defect)    && (rightDecision==Decision::defect))
		result = {Payoff::punishment, Payoff::punishment};
	else
		throw std::logic_error("Decisions made by players are invalid!");
	return result;
}

Payoff PayoffComputer::left(const Decision& leftDecision, const Decision& rightDecision)
{
	return std::get<0>(PayoffComputer::compute(leftDecision, rightDecision));
}

Payoff PayoffComputer::right(const Decision& leftDecision, const Decision& rightDecision)
{
	return std::get<1>(PayoffComputer::compute(leftDecision, rightDecision));
}

std::ostream& PrisonersDilemma::operator<<(std::basic_ostream<char>& os, const Payoff& payoff)
{
	switch(payoff)
	{
		case Payoff::temptation :
			 os << "T";
			break;
		case Payoff::reward :
			 os << "R";
			break;
		case Payoff::punishment :
			 os << "P";
			break;
		case Payoff::suckers :
			 os << "S";
			break;
		default:
			throw std::logic_error("Invalid payoff value given.");
	}
	return os;
}

std::ostream& PrisonersDilemma::operator<<(std::basic_ostream<char>& os, const std::vector<Payoff>& payoffs)
{
	for(const auto& val: payoffs)
	{
		os << val << ", ";
	}
	return os;
}
