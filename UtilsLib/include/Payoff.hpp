#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <iostream>
#include <tuple>
#include <vector>
#include "Decision.hpp"

namespace PrisonersDilemma
{
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

	class PayoffComputer
	{
		public:
			static Payoff left (const Decision& leftDecision, const Decision& rightDecision);
			static Payoff right(const Decision& leftDecision, const Decision& rightDecision);
		private:
			static std::tuple<Payoff, Payoff> compute(const Decision& leftDecision, const Decision& rightDecision);
	};

	unsigned operator+(const PrisonersDilemma::Payoff& lhs, const PrisonersDilemma::Payoff& rhs);
	unsigned operator+(const PrisonersDilemma::Payoff& lhs, const unsigned&                 rhs);
	unsigned operator+(const unsigned&                 lhs, const PrisonersDilemma::Payoff& rhs);

	std::ostream& operator<<(std::basic_ostream<char>& os, const Payoff& payoff);
	std::ostream& operator<<(std::basic_ostream<char>& os, const std::vector<Payoff>& payoffs);
}

#endif
