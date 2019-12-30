#include <Strategy.hpp>

void Strategy::addMatchResult(
	Strategy * partnerStrategy,
	unsigned payoff)
{
	this->payoff.push_back(payoff);
	this->partners.push_back(partnerStrategy);
	return;
}
