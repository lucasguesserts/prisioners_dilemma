#include <Test.hpp>
#include <filesystem>
#include <PrisonersDilemmaFile.hpp>

TestCase("Create file", "[PrisonersDilemmaFile]")
{
	const char * filePath = ".PrisonersDilemmaFileTest_Create_file.h5";
	PrisonersDilemmaFile file(filePath);
	file.close();
	check( std::filesystem::exists(filePath) );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCase("Save championship basic data", "[PrisonersDilemmaFile]")
{
	const unsigned numberOfTurns = 5;
	Championship championship(
		"Save Championship - Basic",
		"Save Championship basic data.",
		numberOfTurns,
		{
			&allC,
			&allD,
			&tft
		}
	);
	// Create file
	const char * filePath = ".PrisonersDilemmaFileTest_save_championship_basic_data.h5";
	PrisonersDilemmaFile file(filePath);
	requireNoThrow( file.save(championship) );
	requireNoThrow( file.close() );
	check( std::filesystem::exists(filePath) );
	// open file
	H5::H5File roFile;
	H5::Group group;
	requireNoThrow( roFile.openFile(filePath, H5F_ACC_RDONLY)   );
	requireNoThrow( group = roFile.openGroup(championship.name) );
	section("name")
	{
		std::string attrData;
		H5::Attribute attribute;
		requireNoThrow( attribute = group.openAttribute("name") );
		requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
		requireNoThrow( attribute.close() );
		check( attrData == championship.name);
	}
	requireNoThrow( group.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}
