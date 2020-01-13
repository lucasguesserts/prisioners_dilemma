#include <Championship.hpp>

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
	return 0;
}
