#include "H5Cpp.h"
#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
#include "Championship.hpp"
#include "PrisonersDilemmaFile.hpp"

const std::string PrisonersDilemmaFile::strategiesGroupName = "/Strategies/";

PrisonersDilemmaFile::PrisonersDilemmaFile(
		const std::string & filePath,
		const unsigned      flags)
	: H5::H5File(filePath, flags)
{}

PrisonersDilemmaFile::PrisonersDilemmaFile(
	const std::string  & filePath,
	const Championship & championship)
	: H5::H5File(filePath, H5F_ACC_TRUNC)
{
	this->save(championship);
	this->close();
	return;
}

void PrisonersDilemmaFile::save(const Championship & championship) const
{
	// TODO: add try/catch
	const H5::Group group = this->createGroup(championship.name);
	PrisonersDilemmaFile::saveAttribute(group, "name"         , championship.name          );
	PrisonersDilemmaFile::saveAttribute(group, "description"  , championship.description   );
	PrisonersDilemmaFile::saveAttribute(group, "numberOfTurns", championship.numberOfTurns );
	for(const auto& player: championship.players)
		this->save(player.strategy);
	for(const auto& player: championship.players)
		this->save(group, player);
	return;
}

void PrisonersDilemmaFile::save(const Strategy * const strategy) const
{
	const H5::Group strategiesGroup = this->getStrategiesGroup();
	const H5::Group thisStrategyGroup = strategiesGroup.createGroup(strategy->name);
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "name",        strategy->name       );
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "shortName",   strategy->shortName  );
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "description", strategy->description);
}

void PrisonersDilemmaFile::save(const H5::Group & championshipGroup, const Player & player) const
{
	const H5::Group playerGroup = championshipGroup.createGroup(player.strategy->name);
	if (!this->nameExists(PrisonersDilemmaFile::strategiesGroupName))
		throw std::runtime_error(PrisonersDilemmaFile::strategiesGroupName + " group does not exists.");
	playerGroup.link(H5L_TYPE_HARD, PrisonersDilemmaFile::strategiesGroupName + player.strategy->name, "strategy");
	for(size_t match=0u ; match<player.partners.size() ; ++match)
		this->savePlayerData(
			championshipGroup,
			playerGroup,
			player.decisions.at(match),
			player.payoff.at(match),
			player.partners.at(match)
		);
	return;
}

// TODO: remove the championship group from the arguments
void PrisonersDilemmaFile::savePlayerData(
	const H5::Group             & championshipGroup,
	const H5::Group             & playerGroup,
	const std::vector<Decision> & decision,
	const std::vector<Payoff>   & payoff,
	const Strategy * const        partnerStrategy
) const {
	const H5::Group partnerGroup = playerGroup.createGroup(partnerStrategy->name);
	partnerGroup.link(H5L_TYPE_SOFT, championshipGroup.getObjName()+"/"+partnerStrategy->name, partnerStrategy->name);
	// TODO: improve this implementation. Perhaps create two functions.
	{
		// Decision dataset
		const H5std_string  datasetName = "decisions";
		const hsize_t dims[] = {decision.size()};
		const H5::DataType fileType(H5::PredType::STD_U8LE);
		const H5::DataType memType (H5::PredType::NATIVE_UCHAR);
		const H5::DataSpace dataspace(1, dims);
		const H5::DataSet dataset = partnerGroup.createDataSet(datasetName, fileType, dataspace);
		dataset.write(decision.data(), memType);
	}
	{
		// payoff dataset
		const H5std_string  datasetName = "payoff";
		const hsize_t dims[] = {payoff.size()};
		const H5::DataType fileType(H5::PredType::STD_U8LE);
		const H5::DataType memType (H5::PredType::NATIVE_UINT);
		const H5::DataSpace dataspace(1, dims);
		const H5::DataSet dataset = partnerGroup.createDataSet(datasetName, fileType, dataspace);
		dataset.write(payoff.data(), memType);
	}
	return;
}

H5::Group PrisonersDilemmaFile::getStrategiesGroup(void) const
{
	return (this->exists     (PrisonersDilemmaFile::strategiesGroupName)) ?
		    this->openGroup  (PrisonersDilemmaFile::strategiesGroupName)  :
		    this->createGroup(PrisonersDilemmaFile::strategiesGroupName)  ;
}

void PrisonersDilemmaFile::saveAttribute(
	const H5::Group   & group,
	const std::string & attributeName,
	const std::string & attributeData
){
	const H5::StrType dtype(H5::PredType::C_S1);
	dtype.setCset(H5T_CSET_UTF8);
	dtype.setSize(H5T_VARIABLE);
	const H5::DataSpace dataspace(H5S_SCALAR);
	const H5::Attribute attribute = group.createAttribute(attributeName, dtype, dataspace);
	attribute.write(dtype, attributeData); 
	return;
}

void PrisonersDilemmaFile::saveAttribute(
	const H5::Group   & group,
	const std::string & attributeName,
	const unsigned      attributeValue
){
	const H5::DataSpace dataspace(H5S_SCALAR);
	const H5::Attribute attribute = group.createAttribute(attributeName.c_str(), H5::PredType::STD_U32LE, dataspace);
	attribute.write(H5::PredType::NATIVE_UINT, &attributeValue); 
	return;
}

// TODO: implement the two functions below using
// some sort of "smart template" to bind
// std::string <-> H5::PredType::C_S1
// unsigned    <-> H5::PredType::NATIVE_UINT
std::string PrisonersDilemmaFile::loadStrAttribute(
	const H5::Group   & group,
	const std::string & attributeName
){
	std::string attrData;
	const H5::Attribute attribute = group.openAttribute(attributeName);
	attribute.read(attribute.getStrType(), attrData);
	return attrData;
}

unsigned PrisonersDilemmaFile::loadUnsignedAttribute(
	const H5::Group   & group,
	const std::string & attributeName
){
	unsigned attrData;
	const H5::Attribute attribute = group.openAttribute(attributeName);
	attribute.read(H5::PredType::NATIVE_UINT, &attrData);
	return attrData;
}
