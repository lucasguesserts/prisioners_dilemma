#ifndef DECISION_HPP
#define DECISION_HPP

namespace PrisonersDilemma
{
	enum class Decision : unsigned char { cooperate, defect };
}

PrisonersDilemma::Decision operator!(const PrisonersDilemma::Decision & d);

#endif
