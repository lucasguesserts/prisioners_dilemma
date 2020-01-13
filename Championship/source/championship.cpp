#include <Championship.hpp>
#include <iostream>
#include <iomanip>

int main()
{
	Championship championship({
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
	});
	championship.compete();
	championship.rank();

	std::cout << std::endl << "Strategies rank:" << std::endl;
	for(unsigned place=0u ; place<championship.players.size() ; place++)
	{
		Player& player = championship.players.at(place);
		std::cout << \
			std::setw(2) << place << " : " << \
			player.strategy->name << " : " << \
			"score = " << player.score()   << \
			std::endl;
	}
	std::cout << std::endl;
	return 0;
}
