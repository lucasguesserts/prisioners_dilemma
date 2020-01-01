#include <Match.hpp>

Match::Match(Player& left, Player& right)
	: leftPlayer(left),
	  rightPlayer(right)
{
	leftDecisions.reserve(Match::numberOfTurns);
	rightDecisions.reserve(Match::numberOfTurns);
	leftPayoff.reserve(Match::numberOfTurns);
	rightPayoff.reserve(Match::numberOfTurns);
	for(unsigned turn=0 ; turn<Match::numberOfTurns ; ++turn)
	{
		leftDecisions.push_back(   leftPlayer.strategy->makeDecision(leftDecisions,  rightDecisions) );
		rightDecisions.push_back( rightPlayer.strategy->makeDecision(rightDecisions, leftDecisions)  );
		leftPayoff.push_back(     PayoffComputer::left (leftDecisions.back(), rightDecisions.back()) );
		rightPayoff.push_back(    PayoffComputer::right(leftDecisions.back(), rightDecisions.back()) );
	}
	return;
}
