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

// TODO: change it to a smaller type
enum class Payoff : unsigned {
	reward     = 1,
	temptation = 0,
	suckers    = 3,
	punishment = 2
};

unsigned operator+(const Payoff&   lhs, const Payoff&   rhs);
unsigned operator+(const Payoff&   lhs, const unsigned& rhs);
unsigned operator+(const unsigned& lhs, const Payoff&   rhs);

class PayoffComputer
{
	public:
		static Payoff left (Decision leftDecision, Decision rightDecision);
		static Payoff right(Decision leftDecision, Decision rightDecision);
	private:
		static std::tuple<Payoff, Payoff> compute(Decision leftDecision, Decision rightDecision);
};

#endif
