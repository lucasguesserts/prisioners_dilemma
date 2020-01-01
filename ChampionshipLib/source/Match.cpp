#include <Match.hpp>

Match::Match(Player& left, Player& right)
	: leftPlayer(left),
	  rightPlayer(right)
{
	this->reserveMemory();
	this->computeDecisionsAndPayoff();
	this->saveMatch();
	return;
}

void Match::reserveMemory(void)
{
	this->leftDecisions.reserve(Match::numberOfTurns);
	this->rightDecisions.reserve(Match::numberOfTurns);
	this->leftPayoff.reserve(Match::numberOfTurns);
	this->rightPayoff.reserve(Match::numberOfTurns);
	return;
}

void Match::computeDecisionsAndPayoff(void)
{
	for(unsigned turn=0 ; turn<Match::numberOfTurns ; ++turn)
	{
		// Compute and store decisions
		this->leftDecisions.push_back(   leftPlayer.strategy->makeDecision(leftDecisions,  rightDecisions) );
		this->rightDecisions.push_back( rightPlayer.strategy->makeDecision(rightDecisions, leftDecisions)  );
		// Compute and store payoffs
		this->leftPayoff.push_back(  PayoffComputer::left (leftDecisions.back(), rightDecisions.back()) );
		this->rightPayoff.push_back( PayoffComputer::right(leftDecisions.back(), rightDecisions.back()) );
	}
	return;
}

void Match::saveMatch(void)
{
	leftPlayer.saveMatch( leftDecisions,  leftPayoff,  rightPlayer.strategy);
	rightPlayer.saveMatch(rightDecisions, rightPayoff, leftPlayer.strategy );
	return;
}
