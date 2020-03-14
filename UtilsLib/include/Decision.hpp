#ifndef DECISION_HPP
#define DECISION_HPP

#include <iostream>
#include <vector>

namespace PrisonersDilemma
{
	enum class Decision : unsigned char { cooperate, defect };

	Decision operator!(const PrisonersDilemma::Decision & d);
	std::ostream& operator<<(std::basic_ostream<char>& os, const Decision& decision);
	std::ostream& operator<<(std::basic_ostream<char>& os, const std::vector<Decision>& decisions);
}


#endif
