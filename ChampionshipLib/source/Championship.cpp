#include <Championship.hpp>
#include <Match.hpp>

void Championship::compete(void)
{
	std::vector<Player>::size_type left, right;
	for(left=0u ; left<(players.size()-1) ; ++left)
		for(right=left ; right<players.size() ; ++right)
			Match(this->players[left], this->players[right]);
	return;
}
