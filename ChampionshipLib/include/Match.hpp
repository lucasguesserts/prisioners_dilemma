#ifndef MATCH_HPP
#define MATCH_HPP

#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Player.hpp"

class Match
{
	public:
		Match(Player& left, Player& right, unsigned numberOfTurns);

		Player &leftPlayer, &rightPlayer;
		unsigned numberOfTurns;
		std::vector<Decision> leftDecisions, rightDecisions;
		std::vector<Payoff>   leftPayoff,    rightPayoff;
	
	private:
		void reserveMemory(void);
		void computeDecisionsAndPayoff(void);
		void saveMatch(void);
};

#endif
