#include <Championship.hpp>
#include <algorithm>
#include <numeric>
#include <iomanip>

Championship::Championship(
	std::string            name,
	std::string            description,
	unsigned               numberOfTurns,
	std::vector<Strategy*> strategies)
	: name(name),
	  description(description),
	  numberOfTurns(numberOfTurns)
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
			Match(this->players[left], this->players[right], this->numberOfTurns);
	return;
}

void Championship::rank(void)
{
	auto compare = [](Player& lhs, Player& rhs){ return lhs.score() < rhs.score(); };
	std::sort(this->players.begin(), this->players.end(), compare);
	return;
}

std::ostream& operator<<(std::ostream& os, Championship& championship)
{
	// This is how it is going to look like:
	//
	// Strategies rank:
	// Place :  Score : Strategy
	//     0 :   1198 : Meta-Regulated Adaptative Tit For Tat
	//     1 :   1201 : Gradual
	//     2 :   1265 : Generous Tit For Tat
	//     3 :   1283 : Adaptative Tit For Tat
	os << std::endl << "Strategies rank:" << std::endl;
	auto divisor = " : ";
	os << "Place" << divisor << " Score" << divisor << "Strategy" << std::endl;
	for(unsigned place=0u ; place<championship.players.size() ; place++)
	{
		Player& player = championship.players.at(place);
		os << \
			std::setw( 5) << std::right << place                   << divisor << \
			std::setw( 6) << std::right << player.score()          << divisor << \
			std::setw(40) << std::left  << player.strategy->name   << \
			std::endl;
	}
	os << std::endl;
	return os;
}
