#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"

class Player
{
	public:
		const Strategy *                     strategy;
		// Make those members private
		std::vector< std::vector<Decision> > decisions;
		std::vector< std::vector<Payoff> >   payoff;
		std::vector<const Strategy *>        partners;

		Player(const Strategy& strategy);
		void saveMatch(
			const std::vector<Decision> & decisions,
			const std::vector<Payoff> &   payoff,
			const Strategy * const        partner);
		unsigned score(void) const;
};

#endif
