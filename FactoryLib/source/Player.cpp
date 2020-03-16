#include <vector>
#include <utility>
#include <numeric>
#include <iostream>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Player.hpp"
using namespace PrisonersDilemma;

bool PrisonersDilemma::operator==(const PlayerData & lhs, const PlayerData & rhs)
{
	return ( lhs.partner   == rhs.partner   ) && \
	       ( lhs.decisions == rhs.decisions ) && \
		   ( lhs.payoffs   == rhs.payoffs   );
}

std::ostream& PrisonersDilemma::operator<<(std::ostream& os, const PlayerData& matchData)
{
	os << "partner: "   << matchData.partner   << ", " << \
	      "decisions: " << matchData.decisions << ", " << \
	      "payoff: "    << matchData.payoffs    ;
	return os;
}

Player::Player(const Identifier identifier, const StrategyCreator& strategyCreator)
	: identifier(identifier), strategyCreator(strategyCreator)
{}

Identifier Player::getIdentifier(void) const
{
	return this->identifier;
}

StrategyPtr Player::getStrategy(void) const
{
	return this->strategyCreator();
}

std::vector<PlayerData> Player::getHistory(void) const
{
	return this->matchHistory;
}

unsigned Player::getScore(void) const
{
	auto sumPayoffFromMatch = [](const PlayerData & matchData) -> unsigned { return std::accumulate(matchData.payoffs.cbegin(), matchData.payoffs.cend(), 0u); };
	return std::accumulate(
		this->matchHistory.cbegin(),
		this->matchHistory.cend(),
		0u,
		[&sumPayoffFromMatch](const unsigned & init, const PlayerData & matchData) -> unsigned { return init + sumPayoffFromMatch(matchData); }
		);
}

void Player::saveMatch(const PlayerData & matchData)
{
	this->matchHistory.push_back(matchData);
	return;
}
