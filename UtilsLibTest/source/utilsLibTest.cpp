#include <vector>
#include <random>
#include <fstream>
#include <filesystem>
#include <stdexcept>

#include <Test.hpp>

TestCase("catch test", "[basic]")
{
	int a, b;
	section("true test")
	{
		a = 3;
		b = 3;
		check( a==b );
		require( a==b );
	}
	section("false test")
	{
		a = 4;
		b = 5;
		checkFalse( a==b );
		requireFalse( a==b );
	}
	return;
}

TestCase("catch floating point test", "[basic]")
{
	double a,b;
	a = 3.1415926535898;
	b = 3.1415926535898;
	require( a==b );
	b = 3.141592;
	require( a==Approx(b) );
	return;
}

TestCase("catch nothrow", "[basic]")
{
	auto thisThrow       = []() -> void { throw std::runtime_error("Test exception"); };
	auto thisDoesntThrow = []() -> void { return; };
	requireThrow  (thisThrow());
	checkThrow    (thisThrow());
	requireNoThrow(thisDoesntThrow());
	checkNoThrow  (thisDoesntThrow());
	return;
}

TestCase("cpp_11_foreach", "[basic]")
{
	std::vector<double> values;
	int nValues = 5;
	double rawValues[] = { 2.71, 3.14, 0.0, -3.14, -2.71 };
	for( int i = 0; i < nValues; ++i ){
		values.push_back( rawValues[ i ] );
	}
	int counter = 0;
	for( double v: values ){
		check( rawValues[counter]==v );
		++counter; 
	}
	return;
}

TestCase("check with a probability", "[basic]")
{
	std::default_random_engine randomGenerator;
	std::uniform_int_distribution<unsigned> uniformDistribution(0, 9);
	auto randFunc = [&randomGenerator, &uniformDistribution](){return uniformDistribution(randomGenerator);};
	checkDiscreteProbability(4u, 0.1, randFunc);
	checkDiscreteProbability(8u, 0.1, randFunc);
	return;
}

TestCase("Create and delete file", "[basic]")
{
	const char *filePath = "./.UtilsLibTest_create_and_delete_file.txt";
	// Remove file if exists
	if (std::filesystem::exists(filePath))
		std::filesystem::remove(filePath);
	// Require a existing file
	std::ofstream file(filePath);
	file << "Hello World!";
	file.close();
	// Check
	check( std::filesystem::exists(filePath) );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}
