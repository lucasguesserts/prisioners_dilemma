#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "Strategy.hpp"
#include "Player.hpp"
#include "Match.hpp"
#include "Championship.hpp"

Championship::Championship(
	const std::string &                   name,
	const std::string &                   description,
	const unsigned                        numberOfTurns,
	const std::vector<const Strategy *> & strategies)
	: name(name),
	  description(description),
	  numberOfTurns(numberOfTurns)
{
	for(auto strategy: strategies)
	{
		this->players.emplace_back(*strategy);
	}
	return;
}

void Championship::compete(void)
{
	for(auto leftPlayer=this->players.begin() ; leftPlayer!=this->players.end() ; ++leftPlayer)
		for(auto rightPlayer=leftPlayer ; rightPlayer!=this->players.end() ; ++rightPlayer)
			Match(*leftPlayer, *rightPlayer, this->numberOfTurns);
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
	for(size_t place=0u ; place<championship.players.size() ; place++)
	{
		const Player& player = championship.players.at(place);
		os << \
			std::setw( 5) << std::right << place                   << divisor << \
			std::setw( 6) << std::right << player.score()          << divisor << \
			std::setw(40) << std::left  << player.strategy->name   << \
			std::endl;
	}
	os << std::endl;
	return os;
}
