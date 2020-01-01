#ifndef MATCH_HPP
#define MATCH_HPP

#include <vector>
#include <Strategies.hpp>
#include <Payoff.hpp>
#include <Player.hpp>

class Match
{
	public:
		Match(Player& left, Player& right);

		static constexpr unsigned numberOfTurns = 5;
		Player &leftPlayer, &rightPlayer;
		std::vector<Decision> leftDecisions, rightDecisions;
		std::vector<Payoff>   leftPayoff,    rightPayoff;
};

#endif
