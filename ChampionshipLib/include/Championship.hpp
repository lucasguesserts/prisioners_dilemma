#ifndef CHAMPIONSHIP_HPP
#define CHAMPIONSHIP_HPP

#include <vector>
#include <Player.hpp>

class Championship
{
	public:
		std::vector<Player> players;

		void compete(void);
};

#endif
