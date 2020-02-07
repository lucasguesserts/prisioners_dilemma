#include "Decision.hpp"

Decision operator!(const Decision & d)
{
	return (d==Decision::cooperate) ? Decision::defect : Decision::cooperate;
}
