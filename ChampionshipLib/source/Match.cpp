#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Player.hpp"
#include "Strategy.hpp"
#include "Match.hpp"

Match::Match(Player& left, Player& right, unsigned numberOfTurns)
	: leftPlayer(left),
	  rightPlayer(right),
	  numberOfTurns(numberOfTurns)
{
	this->reserveMemory();
	this->computeDecisionsAndPayoff();
	this->saveMatch();
	return;
}

void Match::reserveMemory(void)
{
	this->leftDecisions.reserve(this->numberOfTurns);
	this->rightDecisions.reserve(this->numberOfTurns);
	this->leftPayoff.reserve(this->numberOfTurns);
	this->rightPayoff.reserve(this->numberOfTurns);
	return;
}

void Match::computeDecisionsAndPayoff(void)
{
	for(unsigned turn=0 ; turn<this->numberOfTurns ; ++turn)
	{
		auto leftDecision  = leftPlayer.strategy->makeDecision (leftDecisions,  rightDecisions);
		auto rightDecision = rightPlayer.strategy->makeDecision(rightDecisions, leftDecisions );
		// Compute and store decisions
		this->leftDecisions.push_back ( leftDecision  );
		this->rightDecisions.push_back( rightDecision );
		// Compute and store payoffs
		this->leftPayoff.push_back ( PayoffComputer::left (leftDecision , rightDecision) );
		this->rightPayoff.push_back( PayoffComputer::right(leftDecision, rightDecision) );
	}
	return;
}

void Match::saveMatch(void)
{
	if (&leftPlayer == &rightPlayer)
	{
		 leftPlayer.saveMatch( leftDecisions,  leftPayoff,  rightPlayer.strategy);
	}
	else
	{
		 leftPlayer.saveMatch( leftDecisions,  leftPayoff,  rightPlayer.strategy);
		rightPlayer.saveMatch(rightDecisions, rightPayoff, leftPlayer.strategy );
	}
	return;
}
