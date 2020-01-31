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
		requireNoThrow( strategiesGroup = roFile.openGroup(PrisonersDilemmaFile::strategiesGroupName) );
		// TODO: Add sections testing more strategies
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
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCase("Save player basic description", "[PrisonersDilemmaFile]")
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
	championship.compete();
	// Create file
	std::string filePath = ".PrisonersDilemmaFileTest_save_player_basic_data.h5";
	PrisonersDilemmaFile file(filePath);
	requireNoThrow( file.save(championship) );
	requireNoThrow( file.close() );
	check( std::filesystem::exists(filePath) );
	// Load file
	PrisonersDilemmaFile roFile(filePath, H5F_ACC_RDONLY);
	section("always cooperate player")
	{
		H5::Group playerGroup, strategyGroup;
		std::string playerGroupPath = "/" + championship.name + "/" + "Always Cooperate" + "/";
		std::string strategyPath = playerGroupPath + "strategy" + "/";
		requireNoThrow( playerGroup = roFile.openGroup(playerGroupPath) );
		check( playerGroup.exists("strategy") );
		requireNoThrow( strategyGroup = roFile.openGroup(strategyPath) );
		section("name")
		{
			std::string attrName = "name";
			std::string attrData;
			H5::Attribute attribute;
			requireNoThrow( attribute = strategyGroup.openAttribute(attrName) );
			requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
			requireNoThrow( attribute.close() );
			check( attrData == allC.name );
		}
		section("short name")
		{
			std::string attrName = "shortName";
			std::string attrData;
			H5::Attribute attribute;
			requireNoThrow( attribute = strategyGroup.openAttribute(attrName) );
			requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
			requireNoThrow( attribute.close() );
			check( attrData == allC.shortName );
		}
		section("description")
		{
			std::string attrName = "description";
			std::string attrData;
			H5::Attribute attribute;
			requireNoThrow( attribute = strategyGroup.openAttribute(attrName) );
			requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
			requireNoThrow( attribute.close() );
			check( attrData == allC.description );
		}
		requireNoThrow( strategyGroup.close() );
		requireNoThrow( playerGroup.close() );
	}
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCase("Save player competitions", "[PrisonersDilemmaFile]")
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
	championship.compete();
	// Create file
	std::string filePath = ".PrisonersDilemmaFileTest_save_player_competition_result.h5";
	PrisonersDilemmaFile file(filePath);
	requireNoThrow( file.save(championship) );
	requireNoThrow( file.close() );
	check( std::filesystem::exists(filePath) );
	// Load file
	PrisonersDilemmaFile roFile(filePath, H5F_ACC_RDONLY);
	section("always cooperate player")
	{
		H5::Group playerGroup;
		std::string playerGroupPath = "/" + championship.name + "/" + "Always Cooperate" + "/";
		requireNoThrow( playerGroup = roFile.openGroup(playerGroupPath) );
		section("competition with always defect")
		{
			H5::Group partnerGroup;
			std::string partnerGroupPath = playerGroupPath + "Always Defect" + "/";
			requireNoThrow( partnerGroup = roFile.openGroup(partnerGroupPath) );
			section("decisions")
			{
				std::string datasetName = "decisions";
				H5::DataSet dataset;
				requireNoThrow(dataset = partnerGroup.openDataSet(datasetName) );
				std::vector<Decision> datasetData;
				datasetData.resize(numberOfTurns);
				requireNoThrow( dataset.read(datasetData.data(), H5::PredType::NATIVE_UCHAR) );
				std::vector<Decision> correctDatasetData(numberOfTurns, Decision::cooperate);
				check( datasetData == correctDatasetData );
				requireNoThrow( dataset.close() );
			}
			section("payoff")
			{
				std::string datasetName = "payoff";
				H5::DataSet dataset;
				requireNoThrow(dataset = partnerGroup.openDataSet(datasetName) );
				std::vector<Payoff> datasetData;
				datasetData.resize(numberOfTurns);
				requireNoThrow( dataset.read(datasetData.data(), H5::PredType::NATIVE_UINT) );
				std::vector<Payoff> correctDatasetData(numberOfTurns, Payoff::suckers);
				check( datasetData == correctDatasetData );
				requireNoThrow( dataset.close() );
			}
			section("partner player link and its strategy")
			{
				check( partnerGroup.exists("Always Defect") );
				check( partnerGroup.exists("Always Defect/strategy") );
				H5::Group partnerStrategyGroup;
				std::string partnerStrategyGroupPath = partnerGroupPath + "Always Defect" + "/" + "strategy" + "/";
				requireNoThrow( partnerStrategyGroup = roFile.openGroup(partnerStrategyGroupPath) );
				section("name")
				{
					std::string attrName = "name";
					std::string attrData;
					H5::Attribute attribute;
					requireNoThrow( attribute = partnerStrategyGroup.openAttribute(attrName) );
					requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
					requireNoThrow( attribute.close() );
					check( attrData == allD.name );
				}
				section("short name")
				{
					std::string attrName = "shortName";
					std::string attrData;
					H5::Attribute attribute;
					requireNoThrow( attribute = partnerStrategyGroup.openAttribute(attrName) );
					requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
					requireNoThrow( attribute.close() );
					check( attrData == allD.shortName );
				}
				section("description")
				{
					std::string attrName = "description";
					std::string attrData;
					H5::Attribute attribute;
					requireNoThrow( attribute = partnerStrategyGroup.openAttribute(attrName) );
					requireNoThrow( attribute.read(attribute.getStrType(), attrData) );
					requireNoThrow( attribute.close() );
					check( attrData == allD.description );
				}
				requireNoThrow( partnerStrategyGroup.close() );
			}
			requireNoThrow( partnerGroup.close() );
		}
		requireNoThrow( playerGroup.close() );
	}
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}
