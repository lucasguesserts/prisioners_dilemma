#include <vector>
#include <numeric>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Player.hpp"

Player::Player(const Strategy& strategy)
	: strategy(&strategy)
{
	return;
}

void Player::saveMatch(
	const std::vector<Decision> & decisions,
	const std::vector<Payoff> &   payoff,
	const Strategy * const        partner)
{
	this->partners.push_back(partner);
	this->decisions.push_back(decisions);
	this->payoff.push_back(payoff);
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
