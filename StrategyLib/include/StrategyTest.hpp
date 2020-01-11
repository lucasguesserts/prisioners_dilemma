#include <vector>
#include <Decision.hpp>
#include <Strategy.hpp>
#include <Test.hpp>

void checkDecisionHistory(
	std::vector<Decision> strategyDecisions,
	std::vector<Decision> partnerDecisions,
	Strategy & strategy
);
