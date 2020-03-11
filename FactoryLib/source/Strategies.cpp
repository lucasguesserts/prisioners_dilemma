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
