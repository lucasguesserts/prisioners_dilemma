#ifndef MATCH_HPP
#define MATCH_HPP

#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Player.hpp"

namespace PrisonersDilemma
{

	class Match
	{
		public:
			Match(Player& left, Player& right, const unsigned numberOfTurns);

			Player &leftPlayer, &rightPlayer;
			const unsigned numberOfTurns;
			std::vector<Decision> leftDecisions, rightDecisions;
			std::vector<Payoff>   leftPayoff,    rightPayoff;
		
		private:
			void reserveMemory(void);
			void computeDecisionsAndPayoff(void);
			void saveMatch(void);
	};

}

#endif
