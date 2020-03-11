#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <functional>
#include <memory>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"

namespace PrisonersDilemma
{

	class Player
	{
		public:
			const Strategy *                               strategy;
			// Make those members private
			std::vector< std::vector<Decision> >           decisions;
			std::vector< std::vector<Payoff> >             payoff;
			std::vector<const Strategy *>                  partners;
			std::function<std::unique_ptr<Strategy>(void)> getStrategy;

			Player(const Strategy& strategy);
			Player(std::function<std::unique_ptr<Strategy>(void)> strategyCreator)
			{
				this->getStrategy = strategyCreator;
				this->strategy = this->getStrategy().release();
				return;
			}
			void saveMatch(
				const std::vector<Decision> & decisions,
				const std::vector<Payoff> &   payoff,
				const Strategy * const        partner);
			unsigned score(void) const;
	};

}

#endif
