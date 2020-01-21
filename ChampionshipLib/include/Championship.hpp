#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <vector>
#include <iostream>
#include <Player.hpp>
#include <Match.hpp>

class Championship
{
	public:
		std::string         name;
		std::string         description;
		unsigned            numberOfTurns;
		std::vector<Player> players;

		Championship(
			std::string            name,
			std::string            description,
			unsigned               numberOfTurns,
			std::vector<Strategy*> strategies);

		void compete(void);
		void rank(void);
};

std::ostream& operator<<(std::ostream& os, Championship& championship);

#endif
