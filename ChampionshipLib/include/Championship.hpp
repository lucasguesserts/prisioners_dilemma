#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <vector>
#include <iostream>
#include <Player.hpp>
#include <Match.hpp>

class Championship
{
	public:
		std::vector<Player> players;
		unsigned numberOfTurns;

		Championship(std::vector<Strategy*>, unsigned numberOfTurns);
		void compete(void);
		void rank(void);
};

std::ostream& operator<<(std::ostream& os, Championship& championship);

#endif
