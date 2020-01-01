#include <Test.hpp>
#include <Decision.hpp>

TestCase("decision", "[Decision]")
{
	check( Decision::cooperate == Decision::cooperate);
	check( Decision::defect == Decision::defect);
	check( Decision::cooperate != Decision::defect);
	checkFalse( Decision::cooperate == Decision::defect);
	return;
}
