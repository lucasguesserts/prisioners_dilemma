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
	std::string filePath = ".PrisonersDilemmaFileTest_save_championship_basic_data.h5";
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
		check( attrData == championship.name );
	}
	section("description")
	{
		std::string attrData;
		H5::Attribute attribute;
		requireNoThrow( attribute = group.openAttribute("description") );
		requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
		requireNoThrow( attribute.close() );
		check( attrData == championship.description );
	}
	section("number of turns")
	{
		unsigned attrData;
		H5::Attribute attribute;
		requireNoThrow( attribute = group.openAttribute("numberOfTurns") );
		requireNoThrow( attribute.read(H5::PredType::NATIVE_UINT, &attrData) );
		requireNoThrow( attribute.close() );
		check( attrData == championship.numberOfTurns );
	}
	section("strategies")
	{
		H5::Group strategiesGroup;
		requireNoThrow( strategiesGroup = roFile.openGroup(PrisonersDilemmaFile::strategiesGroup) );
		section("Always cooperate")
		{
			H5::Group thisStrategyGroup;
			requireNoThrow( thisStrategyGroup = strategiesGroup.openGroup(allC.name) );
			section("name")
			{
				std::string attrName = "name";
				std::string attrData;
				H5::Attribute attribute;
				requireNoThrow( attribute = thisStrategyGroup.openAttribute(attrName) );
				requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
				requireNoThrow( attribute.close() );
				check( attrData == allC.name );
			}
			section("short name")
			{
				std::string attrName = "shortName";
				std::string attrData;
				H5::Attribute attribute;
				requireNoThrow( attribute = thisStrategyGroup.openAttribute(attrName) );
				requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
				requireNoThrow( attribute.close() );
				check( attrData == allC.shortName );
			}
			section("description")
			{
				std::string attrName = "description";
				std::string attrData;
				H5::Attribute attribute;
				requireNoThrow( attribute = thisStrategyGroup.openAttribute(attrName) );
				requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
				requireNoThrow( attribute.close() );
				check( attrData == allC.description );
			}
			requireNoThrow( thisStrategyGroup.close() );
		}
		requireNoThrow( strategiesGroup.close() );
	}
	requireNoThrow( group.close() );
	requireNoThrow( roFile.close() );
	// std::filesystem::remove(filePath);
	// checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCase("Load championship", "[PrisonersDilemmaFile]")
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
	std::string filePath = ".PrisonersDilemmaFileTest_load_championship.h5";
	PrisonersDilemmaFile file(filePath);
	requireNoThrow( file.save(championship) );
	requireNoThrow( file.close() );
	check( std::filesystem::exists(filePath) );
	// Load championship
	PrisonersDilemmaFile roFile(filePath, H5F_ACC_RDONLY);
	Championship loadedChampionship = roFile.load(championship.name);
	section("basic data")
	{
		check( loadedChampionship.name          == championship.name          );
		check( loadedChampionship.description   == championship.description   );
		check( loadedChampionship.numberOfTurns == championship.numberOfTurns );
	}
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCase("Load strategy", "[PrisonersDilemmaFile]")
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
	std::string filePath = ".PrisonersDilemmaFileTest_load_strategy.h5";
	PrisonersDilemmaFile file(filePath);
	requireNoThrow( file.save(championship) );
	requireNoThrow( file.close() );
	check( std::filesystem::exists(filePath) );
	// Read only file
	PrisonersDilemmaFile roFile(filePath, H5F_ACC_RDONLY);
	requireNoThrow( roFile.loadStrategy("Always Cooperate") );
	requireThrow  ( roFile.loadStrategy("super saiyan"    ) );
	check( &allC == roFile.loadStrategy("Always Cooperate") );
	check( &allD == roFile.loadStrategy("Always Defect"   ) );
	check( &tft  == roFile.loadStrategy("Tit For Tat"     ) );
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}
