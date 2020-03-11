#include <string>
#include "Strategy.hpp"
using namespace PrisonersDilemma;

StrategyDescription::StrategyDescription(
	const std::string & name,
	const std::string & shortName,
	const std::string & description)
: name(name),
  shortName(shortName),
  description(description)
{}

Strategy::Strategy(const StrategyDescription & fullDescription)
	: StrategyDescription(fullDescription)
{}
