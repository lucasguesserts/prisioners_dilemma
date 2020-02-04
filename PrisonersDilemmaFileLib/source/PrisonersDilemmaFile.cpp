#include <H5Cpp.h>
#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include <Decision.hpp>
#include <Payoff.hpp>
#include <Strategy.hpp>
#include <Strategies.hpp>
#include <Player.hpp>
#include <Championship.hpp>
#include <PrisonersDilemmaFile.hpp>

const std::string PrisonersDilemmaFile::strategiesGroupName = "/Strategies/";

PrisonersDilemmaFile::PrisonersDilemmaFile(std::string filePath, unsigned flags)
	: H5::H5File(filePath, flags)
{
	return;
}

void PrisonersDilemmaFile::save(Championship & championship)
{
	// TODO: add try/catch
	H5::Group group = this->createGroup(championship.name);
	PrisonersDilemmaFile::saveAttribute(group, "name"         , championship.name          );
	PrisonersDilemmaFile::saveAttribute(group, "description"  , championship.description   );
	PrisonersDilemmaFile::saveAttribute(group, "numberOfTurns", championship.numberOfTurns );
	for(auto& player: championship.players)
		this->save(player.strategy);
	for(auto& player: championship.players)
		this->save(group, player);
	group.close();
	return;
}

void PrisonersDilemmaFile::save(Strategy *strategy)
{
	H5::Group strategiesGroup = this->getStrategiesGroup();
	H5::Group thisStrategyGroup = strategiesGroup.createGroup(strategy->name);
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "name",        strategy->name       );
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "shortName",   strategy->shortName  );
	PrisonersDilemmaFile::saveAttribute(thisStrategyGroup, "description", strategy->description);
	thisStrategyGroup.close();
	strategiesGroup.close();
}

void PrisonersDilemmaFile::save(H5::Group & championshipGroup, Player & player)
{
	H5::Group playerGroup = championshipGroup.createGroup(player.strategy->name);
	if (!this->exists(PrisonersDilemmaFile::strategiesGroupName))
		throw std::runtime_error(PrisonersDilemmaFile::strategiesGroupName + " group does not exists.");
	playerGroup.link(H5L_TYPE_HARD, PrisonersDilemmaFile::strategiesGroupName + player.strategy->name, "strategy");
	for(size_t match=0 ; match<player.partners.size() ; ++match)
		this->savePlayerData(
			championshipGroup,
			playerGroup,
			player.decisions.at(match),
			player.payoff.at(match),
			player.partners.at(match)
		);
	playerGroup.close();
	return;
}

// TODO: remove the championship group from the arguments
void PrisonersDilemmaFile::savePlayerData(
	H5::Group championshipGroup,
	H5::Group playerGroup,
	std::vector<Decision> decision,
	std::vector<Payoff> payoff,
	Strategy * partnerStrategy
){
	H5::Group partnerGroup = playerGroup.createGroup(partnerStrategy->name);
	partnerGroup.link(H5L_TYPE_SOFT, championshipGroup.getObjName()+"/"+partnerStrategy->name, partnerStrategy->name);
	{
		// Decision dataset
		H5std_string  datasetName = "decisions";
		const hsize_t dims[] = {decision.size()};
		H5::DataType fileType(H5::PredType::STD_U8LE);
		H5::DataType memType (H5::PredType::NATIVE_UCHAR);
		H5::DataSpace dataspace(1, dims);
		H5::DataSet dataset = partnerGroup.createDataSet(datasetName, fileType, dataspace);
		dataset.write(decision.data(), memType);
		fileType.close();
		memType.close();
		dataspace.close();
		dataset.close();
	}
	{
		// payoff dataset
		H5std_string  datasetName = "payoff";
		const hsize_t dims[] = {payoff.size()};
		H5::DataType fileType(H5::PredType::STD_U8LE);
		H5::DataType memType (H5::PredType::NATIVE_UINT);
		H5::DataSpace dataspace(1, dims);
		H5::DataSet dataset = partnerGroup.createDataSet(datasetName, fileType, dataspace);
		dataset.write(payoff.data(), memType);
		fileType.close();
		memType.close();
		dataspace.close();
		dataset.close();
	}
	partnerGroup.close();
	return;
}

H5::Group PrisonersDilemmaFile::getStrategiesGroup(void)
{
	// TODO: add try/catch
	H5::Group strategiesGroup;
	if (this->exists("Strategies"))
		strategiesGroup = this->openGroup(PrisonersDilemmaFile::strategiesGroupName);
	else
		strategiesGroup = this->createGroup(PrisonersDilemmaFile::strategiesGroupName);
	return strategiesGroup;
}

void PrisonersDilemmaFile::saveAttribute(
	H5::Group   group,
	std::string attributeName,
	std::string attributeData
){
	H5::StrType dtype(H5::PredType::C_S1);
	dtype.setCset(H5T_CSET_UTF8);
	dtype.setSize(H5T_VARIABLE);
	H5::DataSpace dataspace(H5S_SCALAR);
	H5::Attribute attribute = group.createAttribute(attributeName, dtype, dataspace);
	attribute.write(dtype, attributeData); 
	dtype.close();
	dataspace.close();
	attribute.close();
	return;
}

void PrisonersDilemmaFile::saveAttribute(
	H5::Group   group,
	std::string attributeName,
	unsigned    attributeValue
){
	H5::DataSpace dataspace(H5S_SCALAR);
	H5::Attribute attribute = group.createAttribute(attributeName.c_str(), H5::PredType::STD_U32LE, dataspace);
	attribute.write(H5::PredType::NATIVE_UINT, &attributeValue); 
	dataspace.close();
	attribute.close();
	return;
}

std::string PrisonersDilemmaFile::loadStrAttribute(
	H5::Group group,
	std::string attributeName
){
	std::string attrData;
	H5::Attribute attribute;
	attribute = group.openAttribute(attributeName);
	attribute.read(attribute.getStrType(), attrData);
	attribute.close();
	return attrData;
}

unsigned PrisonersDilemmaFile::loadUnsignedAttribute(
	H5::Group group,
	std::string attributeName
){
	unsigned attrData;
	H5::Attribute attribute;
	attribute = group.openAttribute(attributeName);
	attribute.read(H5::PredType::NATIVE_UINT, &attrData);
	attribute.close();
	return attrData;
}
