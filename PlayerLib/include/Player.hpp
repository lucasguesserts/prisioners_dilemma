#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <Strategy.hpp>
#include <Decision.hpp>
#include <Payoff.hpp>

class Player
{
	public:
		Strategy *                           strategy;
		std::vector< std::vector<Decision> > decisions;
		std::vector< std::vector<Payoff> >   payoff;
		std::vector<Strategy*>               partners;

		Player(Strategy& strategy);
		void saveMatch(std::vector<Decision> decisions, std::vector<Payoff> payoff, Strategy* partner);
};

#endif
