#include <vector>
#include <utility>
#include <numeric>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Player.hpp"
using namespace PrisonersDilemma;

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

void Player::saveMatch(
	const std::vector<Decision> & decisions,
	const std::vector<Payoff> &   payoff,
	const Identifier              partner)
{
	this->decisions.push_back(decisions);
	this->payoff.push_back(payoff);
	this->partners.push_back(partner);
	return;
}

unsigned Player::score(void) const
{
	auto sumPayoffVector = [](const std::vector<Payoff> & payoff) -> unsigned { return std::accumulate(payoff.cbegin(), payoff.cend(), 0u); };
	return std::accumulate(
		this->payoff.cbegin(),
		this->payoff.cend(),
		0u,
		[&sumPayoffVector](const unsigned & init, const std::vector<Payoff> & payoff) -> unsigned { return init + sumPayoffVector(payoff); }
		);
}
