#define CATCH_CONFIG_MAIN
#include <Test.hpp>
#include <string>
#include <iostream>
#include <Championship.hpp>
#include <PrisonersDilemmaFile.hpp>

TestCase("All strategies championship", "[test_install]")
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

	check( championship.players[0].strategy == &PrisonersDilemma::mratft );

	//Save result in file
	PrisonersDilemma::File file("all_strategies.prisonersdilemma", championship);
	
	return;
}
