#include <string>
#include "Strategy.hpp"

Strategy::Strategy(void)
	: name(""),
	  shortName(""),
	  description("")
{}

Strategy::Strategy(
	const std::string& name,
	const std::string& shortName,
	const std::string& description)
	: name(name),
	  shortName(shortName),
	  description(description)
{}
