#include <string>
#include <Strategy.hpp>

Strategy::Strategy(void)
	: name(""),
	  shortName(""),
	  description("")
{}

Strategy::Strategy(std::string name, std::string shortName, std::string description)
	: name(name),
	  shortName(shortName),
	  description(description)
{}
