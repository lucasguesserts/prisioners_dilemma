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
