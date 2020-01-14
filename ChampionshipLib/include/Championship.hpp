#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <vector>
#include <Player.hpp>
#include <Match.hpp>

class Championship
{
	public:
		std::vector<Player> players;
		unsigned numberOfTurns;

		Championship(std::vector<Strategy*>, unsigned numberOfTurns=5);
		void compete(void);
		void rank(void);
};

#endif
