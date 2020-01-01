#include <Championship.hpp>

Championship::Championship(std::vector<Strategy*> strategies)
{
	this->players.reserve(strategies.size());
	for(Strategy* strategy: strategies)
		this->players.push_back( Player(*strategy) );
	return;
}


void Championship::compete(void)
{
	std::vector<Player>::size_type left, right;
	for(left=0u ; left<this->players.size() ; ++left)
		for(right=left ; right<this->players.size() ; ++right)
			Match(this->players[left], this->players[right]);
	return;
}
