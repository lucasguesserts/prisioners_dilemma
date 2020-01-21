#include <Championship.hpp>
#include <iostream>
#include <iomanip>

int main()
{
	const unsigned numberOfTurns = 50;
	Championship championship(
		"All strategies",
		"Competition among all strategies",
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
	return 0;
}
