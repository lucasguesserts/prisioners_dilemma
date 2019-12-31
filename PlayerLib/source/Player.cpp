#include <Player.hpp>

Player::Player(Strategy& strategy)
	: strategy(&strategy)
{
	return;
}
