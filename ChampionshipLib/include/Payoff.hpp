#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <tuple>
#include <Decision.hpp>

// | A/B       | cooperate | defect |
// | cooperate |    R/R    |   S/T  |
// | defect    |    T/S    |   P/P  |
//
// R: reward     payoff
// T: temptation payoff
// S: sucker's   payoff
// P: punishment payoff

enum class Payoff : unsigned {
	reward     = 1,
	temptation = 0,
	suckers    = 3,
	punishment = 2
};

class PayoffComputer
{
	public:
		static Payoff left (Decision leftDecision, Decision rightDecision);
		static Payoff right(Decision leftDecision, Decision rightDecision);
	private:
		static std::tuple<Payoff, Payoff> compute(Decision leftDecision, Decision rightDecision);
};

#endif
