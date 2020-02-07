#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Strategy.hpp"
#include "Player.hpp"
#include "Match.hpp"

class Championship
{
	// TODO: change 'numberOfTurns' to size_t without breaking PrisonersDilemmaFile
	public:
		const std::string         name;
		const std::string         description;
		const unsigned            numberOfTurns;
		std::vector<Player> players;

		Championship(
			const std::string &                   name,
			const std::string &                   description,
			const unsigned                        numberOfTurns,
			const std::vector<const Strategy *> & strategies);

		void compete(void);
		void rank(void);
};

std::ostream& operator<<(std::ostream& os, Championship& championship);

#endif
