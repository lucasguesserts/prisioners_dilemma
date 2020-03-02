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
	Championship championship(
		"All strategies",
		"Competition among all strategies.",
		numberOfTurns,
		{
			&allC   ,
			&allD   ,
			&moon   ,
			&grim   ,
			&pvl    ,
			&gradual,
			&sm     ,
			&hm     ,
			&np     ,
			&rp     ,
			&sg     ,
			&pb     ,
			&fbf    ,
			&tft    ,
			&tftt   ,
			&ttft   ,
			&rtft   ,
			&gtft   ,
			&stft   ,
			&htft   ,
			&atft   ,
			&mratft ,
		}
	);
	championship.compete();
	championship.rank();
	std::cout << championship;

	//Save result in file
	PrisonersDilemmaFile file("all_strategies.prisonersdilemma", championship);
	
	return 0;
}
