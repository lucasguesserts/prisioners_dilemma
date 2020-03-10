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
using namespace PrisonersDilemma;

class ChampionshipFixture
{
	public:
		const unsigned numberOfTurns = 5;
		Championship championship;
		ChampionshipFixture(void)
			: championship({"Test Championship","For test.", numberOfTurns}, {&allC, &allD, &tft})
		{
			this->championship.compete();
			return;
		}
};

TestCaseMethod(ChampionshipFixture, "Create file", "[File]")
{
	std::string filePath = ".FileTest_Create_file.h5";
	File file(filePath, championship);
	file.close();
	check( std::filesystem::exists(filePath) );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCaseMethod(ChampionshipFixture, "Save championship basic data", "[File]")
{
	// Create file
	std::string filePath = ".FileTest_save_championship_basic_data.h5";
	File file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// open file
	File roFile(filePath);
	H5::Group group;
	requireNoThrow( group = roFile.openGroup(championship.name) );
	check( File::loadStrAttribute     (group, "name")          == championship.name          );
	check( File::loadStrAttribute     (group, "description")   == championship.description   );
	check( File::loadUnsignedAttribute(group, "numberOfTurns") == championship.numberOfTurns );
	section("strategies")
	{
		H5::Group strategiesGroup;
		requireNoThrow( strategiesGroup = roFile.openGroup(File::strategiesGroupName) );
		// TODO: add more strategies
		section("Always cooperate")
		{
			H5::Group thisStrategyGroup;
			requireNoThrow( thisStrategyGroup = strategiesGroup.openGroup(allC.name) );
			check( File::loadStrAttribute(thisStrategyGroup, "name")        == allC.name        );
			check( File::loadStrAttribute(thisStrategyGroup, "shortName")   == allC.shortName   );
			check( File::loadStrAttribute(thisStrategyGroup, "description") == allC.description );
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

TestCaseMethod(ChampionshipFixture, "Save player basic description", "[File]")
{
	// Create file
	std::string filePath = ".FileTest_save_player_basic_data.h5";
	File file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// Load file
	File roFile(filePath);
	// TODO: add more players
	section("always cooperate player")
	{
		H5::Group playerGroup, strategyGroup;
		std::string playerGroupPath = "/" + championship.name + "/" + "Always Cooperate" + "/";
		std::string strategyPath = playerGroupPath + "strategy" + "/";
		requireNoThrow( playerGroup = roFile.openGroup(playerGroupPath) );
		check( playerGroup.exists("strategy") );
		requireNoThrow( strategyGroup = roFile.openGroup(strategyPath) );
		check( File::loadStrAttribute(strategyGroup, "name")        == allC.name        );
		check( File::loadStrAttribute(strategyGroup, "shortName")   == allC.shortName   );
		check( File::loadStrAttribute(strategyGroup, "description") == allC.description );
		requireNoThrow( strategyGroup.close() );
		requireNoThrow( playerGroup.close() );
	}
	// Close and delete file
	requireNoThrow( roFile.close() );
	std::filesystem::remove(filePath);
	checkFalse( std::filesystem::exists(filePath) );
	return;
}

TestCaseMethod(ChampionshipFixture, "Save player competitions", "[File]")
{
	// Create file
	std::string filePath = ".FileTest_save_player_competition_result.h5";
	File file(filePath, championship);
	check( std::filesystem::exists(filePath) );
	// Load file
	File roFile(filePath);
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
				check( File::loadDecisions(partnerGroup,numberOfTurns) == correctDatasetData );
			}
			section("payoff")
			{
				std::vector<Payoff> correctDatasetData(numberOfTurns, Payoff::suckers);
				check( File::loadPayoff(partnerGroup,numberOfTurns) == correctDatasetData );
			}
			section("partner player link and its strategy")
			{
				check( partnerGroup.exists("Always Defect") );
				check( partnerGroup.exists("Always Defect/strategy") );
				H5::Group partnerStrategyGroup;
				std::string partnerStrategyGroupPath = partnerGroupPath + "Always Defect" + "/" + "strategy" + "/";
				requireNoThrow( partnerStrategyGroup = roFile.openGroup(partnerStrategyGroupPath) );
				check( File::loadStrAttribute(partnerStrategyGroup, "name")        == allD.name        );
				check( File::loadStrAttribute(partnerStrategyGroup, "shortName")   == allD.shortName   );
				check( File::loadStrAttribute(partnerStrategyGroup, "description") == allD.description );
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
