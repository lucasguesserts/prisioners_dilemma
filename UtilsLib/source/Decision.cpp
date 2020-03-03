#include "Decision.hpp"
using namespace PrisonersDilemma;

Decision operator!(const Decision & d)
{
	return (d==Decision::cooperate) ? Decision::defect : Decision::cooperate;
}
