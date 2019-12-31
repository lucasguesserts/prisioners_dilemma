#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <Decision.hpp>
#include <Strategy.hpp>

class Player
{
	public:
		Strategy *                           strategy;
		std::vector< std::vector<Decision> > decisions;
		std::vector< std::vector<unsigned> > payoff;
		std::vector<Strategy>                partners;

		Player(Strategy& strategy);
};

#endif
