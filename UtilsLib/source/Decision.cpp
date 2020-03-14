#include <stdexcept>
#include "Decision.hpp"
using namespace PrisonersDilemma;

Decision PrisonersDilemma::operator!(const Decision & d)
{
	return (d==Decision::cooperate) ? Decision::defect : Decision::cooperate;
}

std::ostream& PrisonersDilemma::operator<<(std::basic_ostream<char>& os, const Decision& decision)
{
	switch(decision)
	{
		case Decision::cooperate :
			 os << "C";
			break;
		case Decision::defect :
			 os << "D";
			break;
		default:
			throw std::logic_error("Invalid decision value given.");
	}
	return os;
}

std::ostream& PrisonersDilemma::operator<<(std::basic_ostream<char>& os, const std::vector<Decision>& decisions)
{
	for(const auto& val: decisions)
	{
		os << val << ", ";
	}
	return os;
}
