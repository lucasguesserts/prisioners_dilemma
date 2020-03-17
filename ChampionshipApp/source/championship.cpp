#include <string>
#include <vector>
#include <iostream>
#include <H5Cpp.h>
#include <Decision.hpp>
#include <Payoff.hpp>
#include <Strategy.hpp>
#include <Strategies.hpp>
#include <Player.hpp>
#include <Championship.hpp>
#include <PrisonersDilemmaFile.hpp>

int main()
{

	// Championship
	const unsigned numberOfTurns = 50;
	PrisonersDilemma::Championship championship(
		{
			"All strategies",
			"Competition among all strategies.",
			numberOfTurns
		},
		{
			&PrisonersDilemma::allC   ,
			&PrisonersDilemma::allD   ,
			&PrisonersDilemma::moon   ,
			&PrisonersDilemma::grim   ,
			&PrisonersDilemma::pvl    ,
			&PrisonersDilemma::gradual,
			&PrisonersDilemma::sm     ,
			&PrisonersDilemma::hm     ,
			&PrisonersDilemma::np     ,
			&PrisonersDilemma::rp     ,
			&PrisonersDilemma::sg     ,
			&PrisonersDilemma::pb     ,
			&PrisonersDilemma::fbf    ,
			&PrisonersDilemma::tft    ,
			&PrisonersDilemma::tftt   ,
			&PrisonersDilemma::ttft   ,
			&PrisonersDilemma::rtft   ,
			&PrisonersDilemma::gtft   ,
			&PrisonersDilemma::stft   ,
			&PrisonersDilemma::htft   ,
			&PrisonersDilemma::atft   ,
			&PrisonersDilemma::mratft ,
		}
	);
	championship.compete();
	championship.rank();
	std::cout << championship;

	//Save result in file
	PrisonersDilemma::File file("all_strategies.prisonersdilemma", championship);
	
	return 0;
}
