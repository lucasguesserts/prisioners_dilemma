#include <vector>
#include <numeric>
#include <Decision.hpp>
#include <Payoff.hpp>
#include <Strategy.hpp>
#include <Player.hpp>

Player::Player(Strategy& strategy)
	: strategy(&strategy)
{
	return;
}

void Player::saveMatch(
	std::vector<Decision> decisions,
	std::vector<Payoff> payoff,
	Strategy* partner)
{
	this->partners.push_back(partner);
	this->decisions.push_back(decisions);
	this->payoff.push_back(payoff);
	return;
}

unsigned Player::score(void)
{
	auto sumPayoffVector = [](std::vector<Payoff> payoff) -> unsigned { return std::accumulate(payoff.cbegin(), payoff.cend(), 0u); };
	return std::accumulate(
		this->payoff.cbegin(),
		this->payoff.cend(),
		0u,
		[&sumPayoffVector](unsigned init, std::vector<Payoff> payoff) -> unsigned { return init + sumPayoffVector(payoff); }
		);
}
