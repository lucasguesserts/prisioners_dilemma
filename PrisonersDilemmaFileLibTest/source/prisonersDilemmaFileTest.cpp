#include <Test.hpp>
#include <filesystem>
#include <PrisonersDilemmaFile.hpp>

TestCase("Create file", "[PrisonersDilemmaFile]")
{
	std::string filePath = ".PrisonersDilemmaFileTest_Create_file.h5";
	PrisonersDilemmaFile file(filePath);
	file.close();
	check( std::filesystem::exists(filePath) );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}
