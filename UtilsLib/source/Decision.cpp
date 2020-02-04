#include "Decision.hpp"

Decision operator!(const Decision &d)
{
	return static_cast<Decision>( ! static_cast<bool>(d) );
}
