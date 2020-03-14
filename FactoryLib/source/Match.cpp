#include <vector>
#include <utility>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Player.hpp"
#include "Strategy.hpp"
#include "Match.hpp"
using namespace PrisonersDilemma;

Match::Match(Player& left, Player& right, const unsigned numberOfTurns)
	: numberOfTurns(numberOfTurns),
	  players{left, right}
{
	this->reserveMemory();
	this->computeDecisionsAndPayoff();
	this->saveMatch();
	return;
}

void Match::reserveMemory(void)
{
	this->strategies.first = std::move(players.first.getStrategy());
	this->strategies.second = std::move(players.second.getStrategy());
	this->decisions.first.reserve(this->numberOfTurns);
	this->decisions.second.reserve(this->numberOfTurns);
	this->payoffs.first.reserve(this->numberOfTurns);
	this->payoffs.second.reserve(this->numberOfTurns);
	return;
}

void Match::computeDecisionsAndPayoff(void)
{
	std::pair<Decision,Decision> turnDecisions;
	std::pair<Decision,Decision> lastTurnDecisions;
	{
		//turn 0
		turnDecisions.first  = this->strategies.first->makeInitialDecision();
		turnDecisions.second = this->strategies.second->makeInitialDecision();
		this->decisions.first.push_back(turnDecisions.first);
		this->decisions.second.push_back(turnDecisions.second);
		this->payoffs.first.emplace_back ( PayoffComputer::left(turnDecisions.first,  turnDecisions.second) );
		this->payoffs.second.emplace_back( PayoffComputer::right(turnDecisions.first, turnDecisions.second) );
		lastTurnDecisions = turnDecisions;
	}

	for(unsigned turn=1 ; turn<this->numberOfTurns ; ++turn)
	{
		turnDecisions.first  = this->strategies.first->makeDecision(lastTurnDecisions.first);
		turnDecisions.second = this->strategies.second->makeDecision(lastTurnDecisions.second);
		// Store decisions
		this->decisions.first.push_back (turnDecisions.first);
		this->decisions.second.push_back(turnDecisions.second);
		// Compute and store payoffs
		this->payoffs.first.emplace_back ( PayoffComputer::left(turnDecisions.first,  turnDecisions.second) );
		this->payoffs.second.emplace_back( PayoffComputer::right(turnDecisions.first, turnDecisions.second) );
		// Update last turn decisions
		lastTurnDecisions = turnDecisions;
	}
	return;
}

void Match::saveMatch(void)
{
	if (this->players.first.getIdentifier() == this->players.second.getIdentifier())
	{
		 this->players.first.saveMatch({this->players.first.getIdentifier(), this->decisions.first, this->payoffs.first});
	}
	else
	{
		 this->players.first.saveMatch ({ this->players.second.getIdentifier(), this->decisions.first,  this->payoffs.first  });
		 this->players.second.saveMatch({ this->players.first.getIdentifier(),  this->decisions.second, this->payoffs.second });
	}
	return;
}
