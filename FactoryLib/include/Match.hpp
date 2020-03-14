#ifndef FACTORY_MATCH_HPP
#define FACTORY_MATCH_HPP

#include <vector>
#include <utility>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Player.hpp"

namespace PrisonersDilemma
{

	class Match
	{
		public:
			Match(Player& left, Player& right, const unsigned numberOfTurns);

		private:
			const unsigned                                          numberOfTurns;
			std::pair<Player&, Player&>                             players;
			std::pair<std::vector<Decision>, std::vector<Decision>> decisions;
			std::pair<std::vector<Payoff>, std::vector<Payoff>>     payoffs;
			std::pair<StrategyPtr, StrategyPtr>                     strategies;

			void reserveMemory(void);
			void computeDecisionsAndPayoff(void);
			void saveMatch(void);
	};

}

#endif
