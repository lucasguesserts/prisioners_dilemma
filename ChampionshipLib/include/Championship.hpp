#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include "Strategy.hpp"
#include "Player.hpp"
#include "Match.hpp"

namespace PrisonersDilemma
{

	struct ChampionshipDescription
	{
		const std::string name;
		const std::string description;
		const unsigned    numberOfTurns;

		ChampionshipDescription(
			const std::string & name,
			const std::string & description,
			const unsigned      numberOfTurns
		);
	};

	class Championship: public ChampionshipDescription
	{
		// TODO: change 'numberOfTurns' to size_t without breaking PrisonersDilemmaFile
		public:
			std::vector<Player>       players;

			Championship(
				const ChampionshipDescription &       fullDescription,
				const std::vector<const Strategy *> & strategies);

			Championship(
				const ChampionshipDescription &       fullDescription,
				const std::vector<std::function<std::unique_ptr<Strategy>(void)>> & strategyCreators)
				: ChampionshipDescription(fullDescription)
			{
				for(auto strategyCreator: strategyCreators)
					this->players.emplace_back(strategyCreator);
				return;
			}

			void compete(void);
			void rank(void);
	};

	std::ostream& operator<<(std::ostream& os, const ChampionshipDescription& championshipDescription);
	std::ostream& operator<<(std::ostream& os, const Championship& championship);

}

#endif
