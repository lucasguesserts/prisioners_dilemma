#ifndef FACTORY_PLAYER_HPP
#define FACTORY_PLAYER_HPP

#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"

namespace PrisonersDilemma
{

	using Identifier = unsigned;

	// It is necessary to implement an identifier
	// for the player which is unique inside a
	// championship.
	class Player
	{
		public:
			Player(const Identifier identifier, const StrategyCreator& strategyCreator);
			Identifier getIdentifier(void) const;
			StrategyPtr getStrategy(void) const;
			unsigned score(void) const;
			void saveMatch(
				const std::vector<Decision> & decisions,
				const std::vector<Payoff> &   payoff,
				const Identifier              partner);
		private:
			const Identifier                               identifier;
			StrategyCreator                                strategyCreator;
			std::vector< std::vector<Decision> >           decisions;
			std::vector< std::vector<Payoff> >             payoff;
			std::vector<Identifier>                        partners;
	};

}

#endif
