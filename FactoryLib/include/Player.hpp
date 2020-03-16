#ifndef FACTORY_PLAYER_HPP
#define FACTORY_PLAYER_HPP

#include <vector>
#include <iostream>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"

namespace PrisonersDilemma
{

	using Identifier = unsigned;

	struct PlayerData
	{
		Identifier            partner;
		std::vector<Decision> decisions;
		std::vector<Payoff>   payoffs;
	};

	bool operator==(const PlayerData & lhs, const PlayerData & rhs);
	std::ostream& operator<<(std::ostream& os, const PlayerData& matchData);

	class Player
	{
		public:
			Player(const Identifier identifier, const StrategyCreator& strategyCreator);
			Identifier                getIdentifier(void) const;
			StrategyPtr               getStrategy  (void) const;
			std::vector<PlayerData>   getHistory   (void) const;
			unsigned                  getScore     (void) const;
			void                      saveMatch    (const PlayerData & matchData);
		private:
			const Identifier        identifier;
			const StrategyCreator   strategyCreator;
			std::vector<PlayerData> matchHistory;
	};

}

#endif
