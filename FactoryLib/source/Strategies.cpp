// TODO: add more `return` statements
// when it makes sense to do so.

#include <cstddef>
#include <random>
#include <iterator>
#include <utility>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include "Strategies.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
using namespace PrisonersDilemma;

// ------------------ Always Cooperate -----------------------

AlwaysCooperate::AlwaysCooperate(void)
: Strategy(
	{
		"Always Cooperate",
		"AllC",
		"Always cooperate."
	})
{}

Decision AlwaysCooperate::makeInitialDecision(void)
{
	return Decision::cooperate;
}

Decision AlwaysCooperate::makeDecision([[maybe_unused]] const Decision & partnerLastDecision)
{
	return Decision::cooperate;
}

std::function<std::unique_ptr<Strategy>(void)> AlwaysCooperate::creator(void)
{
	return [](){ return static_cast<std::unique_ptr<Strategy>> (std::make_unique<AlwaysCooperate>()); };
}

// ------------------ Always Defect -----------------------

AlwaysDefect::AlwaysDefect(void)
: Strategy(
	{
		"Always Defect",
		"AllD",
		"Always defect."
	})
{}

Decision AlwaysDefect::makeInitialDecision(void)
{
	return Decision::defect;
}

Decision AlwaysDefect::makeDecision([[maybe_unused]] const Decision & partnerLastDecision)
{
	return Decision::defect;
}

std::function<std::unique_ptr<Strategy>(void)> AlwaysDefect::creator(void)
{
	return [](){ return static_cast<std::unique_ptr<Strategy>> (std::make_unique<AlwaysDefect>()); };
}

// ------------------ Tit For Tat -----------------------

TitForTat::TitForTat(void)
: Strategy(
	{
		"Tit For Tat",
		"TFT",
		"Start cooperating. Copy opponent's last move afterwards."
	})
{}

Decision TitForTat::makeInitialDecision(void)
{
	return Decision::cooperate;
}

Decision TitForTat::makeDecision(const Decision & partnerLastDecision)
{
	return partnerLastDecision;
}

std::function<std::unique_ptr<Strategy>(void)> TitForTat::creator(void)
{
	return [](){ return static_cast<std::unique_ptr<Strategy>> (std::make_unique<TitForTat>()); };
}

// ------------------ Tit For Tat -----------------------

NaiveProber::NaiveProber(double probabilityOfDefecting)
: Strategy(
	{
		"Naive Prober",
		"NP",
		"Like Tit for Tat, but ocasionally defects with a small probability."
	}),
  probabilityOfDefecting(probabilityOfDefecting)
{
	if ((this->probabilityOfDefecting < 0.0) || (1.0 < this->probabilityOfDefecting))
		throw std::domain_error("Probability of defecting in Naive Prober has to be between 0.0 and 1.0.");
	return;
}

Decision NaiveProber::makeInitialDecision(void)
{
	if   (this->decidedRandomlyToDefect()) return Decision::defect   ;
	else                                   return Decision::cooperate;
}

Decision NaiveProber::makeDecision(const Decision & partnerLastDecision)
{
	if   (this->decidedRandomlyToDefect()) return Decision::defect   ;
	else                                   return partnerLastDecision;
}

std::function<std::unique_ptr<Strategy>(void)> NaiveProber::creator(double probabilityOfDefecting)
{
	return [probabilityOfDefecting](){
		return static_cast<std::unique_ptr<Strategy>>(
				std::make_unique<NaiveProber>(
					probabilityOfDefecting
				)
		);
	};
}

bool NaiveProber::decidedRandomlyToDefect(void) const
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator) < this->probabilityOfDefecting;
}
