#include "H5Cpp.h"
#include <string>
#include <vector>
#include "Filesystem.hpp"
#include "Test.hpp"
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
#include "Championship.hpp"
#include "PrisonersDilemmaFile.hpp"

class ChampionshipFixture
{
	public:
		const unsigned numberOfTurns = 5;
		Championship championship;
		ChampionshipFixture(void)
			: championship("Test Championship","For test.", numberOfTurns, {&allC,	&allD, &tft})
		{
			this->championship.compete();
			return;
		}
};

TestCaseMethod(ChampionshipFixture, "Create file", "[PrisonersDilemmaFile]")
{
	std::string filePath = ".PrisonersDilemmaFileTest_Create_file.h5";
	PrisonersDilemmaFile file(filePath, championship);
	file.close();
	check( std::filesystem::exists(filePath) );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCaseMethod(ChampionshipFixture, "Save championship basic data", "[PrisonersDilemmaFile]")
{
	// Create file
	std::string filePath = ".PrisonersDilemmaFileTest_save_championship_basic_data.h5";
	PrisonersDilemmaFile file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// open file
	PrisonersDilemmaFile roFile(filePath);
	H5::Group group;
	requireNoThrow( group = roFile.openGroup(championship.name) );
	check( PrisonersDilemmaFile::loadStrAttribute     (group, "name")          == championship.name          );
	check( PrisonersDilemmaFile::loadStrAttribute     (group, "description")   == championship.description   );
	check( PrisonersDilemmaFile::loadUnsignedAttribute(group, "numberOfTurns") == championship.numberOfTurns );
	section("strategies")
	{
		H5::Group strategiesGroup;
		requireNoThrow( strategiesGroup = roFile.openGroup(PrisonersDilemmaFile::strategiesGroupName) );
		// TODO: add more strategies
		section("Always cooperate")
		{
			H5::Group thisStrategyGroup;
			requireNoThrow( thisStrategyGroup = strategiesGroup.openGroup(allC.name) );
			check( PrisonersDilemmaFile::loadStrAttribute(thisStrategyGroup, "name")        == allC.name        );
			check( PrisonersDilemmaFile::loadStrAttribute(thisStrategyGroup, "shortName")   == allC.shortName   );
			check( PrisonersDilemmaFile::loadStrAttribute(thisStrategyGroup, "description") == allC.description );
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

TestCaseMethod(ChampionshipFixture, "Save player basic description", "[PrisonersDilemmaFile]")
{
	// Create file
	std::string filePath = ".PrisonersDilemmaFileTest_save_player_basic_data.h5";
	PrisonersDilemmaFile file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// Load file
	PrisonersDilemmaFile roFile(filePath);
	// TODO: add more players
	section("always cooperate player")
	{
		H5::Group playerGroup, strategyGroup;
		std::string playerGroupPath = "/" + championship.name + "/" + "Always Cooperate" + "/";
		std::string strategyPath = playerGroupPath + "strategy" + "/";
		requireNoThrow( playerGroup = roFile.openGroup(playerGroupPath) );
		check( playerGroup.exists("strategy") );
		requireNoThrow( strategyGroup = roFile.openGroup(strategyPath) );
		check( PrisonersDilemmaFile::loadStrAttribute(strategyGroup, "name")        == allC.name        );
		check( PrisonersDilemmaFile::loadStrAttribute(strategyGroup, "shortName")   == allC.shortName   );
		check( PrisonersDilemmaFile::loadStrAttribute(strategyGroup, "description") == allC.description );
		requireNoThrow( strategyGroup.close() );
		requireNoThrow( playerGroup.close() );
	}
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCaseMethod(ChampionshipFixture, "Save player competitions", "[PrisonersDilemmaFile]")
{
	// Create file
	std::string filePath = ".PrisonersDilemmaFileTest_save_player_competition_result.h5";
	PrisonersDilemmaFile file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// Load file
	PrisonersDilemmaFile roFile(filePath);
	section("always cooperate player")
	{
		H5::Group playerGroup;
		std::string playerGroupPath = "/" + championship.name + "/" + "Always Cooperate" + "/";
		requireNoThrow( playerGroup = roFile.openGroup(playerGroupPath) );
		// TODO: add more partners
		section("competition with always defect")
		{
			H5::Group partnerGroup;
			std::string partnerGroupPath = playerGroupPath + "Always Defect" + "/";
			requireNoThrow( partnerGroup = roFile.openGroup(partnerGroupPath) );
			section("decisions")
			{
				std::vector<Decision> correctDatasetData(numberOfTurns, Decision::cooperate);
				check( PrisonersDilemmaFile::loadDecisions(partnerGroup,numberOfTurns) == correctDatasetData );
			}
			section("payoff")
			{
				std::vector<Payoff> correctDatasetData(numberOfTurns, Payoff::suckers);
				check( PrisonersDilemmaFile::loadPayoff(partnerGroup,numberOfTurns) == correctDatasetData );
			}
			section("partner player link and its strategy")
			{
				check( partnerGroup.exists("Always Defect") );
				check( partnerGroup.exists("Always Defect/strategy") );
				H5::Group partnerStrategyGroup;
				std::string partnerStrategyGroupPath = partnerGroupPath + "Always Defect" + "/" + "strategy" + "/";
				requireNoThrow( partnerStrategyGroup = roFile.openGroup(partnerStrategyGroupPath) );
				check( PrisonersDilemmaFile::loadStrAttribute(partnerStrategyGroup, "name")        == allD.name        );
				check( PrisonersDilemmaFile::loadStrAttribute(partnerStrategyGroup, "shortName")   == allD.shortName   );
				check( PrisonersDilemmaFile::loadStrAttribute(partnerStrategyGroup, "description") == allD.description );
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
