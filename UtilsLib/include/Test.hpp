#ifndef UTILS_TEST_H
#define UTILS_TEST_H

#include "catch.hpp"

#define TestCase TEST_CASE
#define section SECTION

#define check CHECK
#define checkFalse CHECK_FALSE
#define require REQUIRE
#define requireFalse REQUIRE_FALSE

#define requireThrow REQUIRE_THROWS
#define checkThrow CHECK_THROWS
#define requireNoThrow REQUIRE_NOTHROW
#define checkNoThrow CHECK_NOTHROW

#define checkDiscreteProbability(val, prob, func)\
   check( probability(val, func) == Approx(prob).epsilon(0.05) )

template <typename Val, typename RandomClass>
double probability(Val val, RandomClass func)
{
	const unsigned N_repetitions = 1E+5;
	unsigned counter = 0;
	for (unsigned i=0 ; i<N_repetitions ; ++i)
		if(func() == val)
			++counter;
	return static_cast<double>(counter) / N_repetitions;
}

#endif
