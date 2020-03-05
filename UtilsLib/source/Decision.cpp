#include "Decision.hpp"
using namespace PrisonersDilemma;

Decision PrisonersDilemma::operator!(const Decision & d)
{
	return (d==Decision::cooperate) ? Decision::defect : Decision::cooperate;
}
