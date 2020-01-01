#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <vector>
#include <Player.hpp>
#include <Match.hpp>

class Championship
{
	public:
		std::vector<Player> players;

		Championship(std::vector<Strategy*>);
		void compete(void);
};

#endif
