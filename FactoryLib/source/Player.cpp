#include <vector>
#include <utility>
#include <numeric>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Player.hpp"
using namespace PrisonersDilemma;

bool PrisonersDilemma::operator==(const MatchData & lhs, const MatchData & rhs)
{
	return ( lhs.partner   == rhs.partner   ) && \
	       ( lhs.decisions == rhs.decisions ) && \
		   ( lhs.payoffs   == rhs.payoffs   );
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

std::vector<MatchData> Player::getHistory(void) const
{
	return this->matchHistory;
}

unsigned Player::getScore(void) const
{
	auto sumPayoffFromMatch = [](const MatchData & matchData) -> unsigned { return std::accumulate(matchData.payoffs.cbegin(), matchData.payoffs.cend(), 0u); };
	return std::accumulate(
		this->matchHistory.cbegin(),
		this->matchHistory.cend(),
		0u,
		[&sumPayoffFromMatch](const unsigned & init, const MatchData & matchData) -> unsigned { return init + sumPayoffFromMatch(matchData); }
		);
}

void Player::saveMatch(const MatchData & matchData)
{
	this->matchHistory.push_back(matchData);
	return;
}
