#include <PrisonersDilemmaFile.hpp>

const std::string PrisonersDilemmaFile::strategiesGroup = "/Strategies/";

PrisonersDilemmaFile::PrisonersDilemmaFile(std::string filePath, int flags)
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
	if (!this->exists(PrisonersDilemmaFile::strategiesGroup))
		throw std::runtime_error(PrisonersDilemmaFile::strategiesGroup + " group does not exists.");
	playerGroup.link(H5L_TYPE_HARD, PrisonersDilemmaFile::strategiesGroup + player.strategy->name, "strategy");
	playerGroup.close();
	return;
}

H5::Group PrisonersDilemmaFile::getStrategiesGroup(void)
{
	// TODO: add try/catch
	std::string strategiesGroupName = PrisonersDilemmaFile::strategiesGroup;
	H5::Group strategiesGroup;
	if (this->exists("Strategies"))
		strategiesGroup = this->openGroup(strategiesGroupName);
	else
		strategiesGroup = this->createGroup(strategiesGroupName);
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

Championship PrisonersDilemmaFile::load(std::string groupName)
{
	H5::Group group = this->openGroup(groupName);
	std::string championshipName = PrisonersDilemmaFile::loadStrAttribute(group, "name");
	std::string championshipDescription = PrisonersDilemmaFile::loadStrAttribute(group, "description");
	unsigned numberOfTurns = PrisonersDilemmaFile::loadUnsignedAttribute(group, "numberOfTurns");

	return Championship(
		championshipName,
		championshipDescription,
		numberOfTurns,
		{}
	);
}

Strategy* PrisonersDilemmaFile::loadStrategy(std::string strategyName)
{
	std::string groupLocation = PrisonersDilemmaFile::strategiesGroup + strategyName + "/";
	try
	{
		Strategy * strategy;
		H5::Group group = this->openGroup(groupLocation);
		std::string name        = loadStrAttribute(group, "name");
		std::string shortName   = loadStrAttribute(group, "shortName");
		std::string description = loadStrAttribute(group, "description");
		group.close();
		strategy = findStrategy(name, shortName, description);
		if (strategy == nullptr)
			throw std::runtime_error("The strategy loaded is not implemented.\nName: " + name + "\nshort name: " + shortName + "\nDescription: " + description);
		return strategy;
	}
	catch(H5::GroupIException &groupException)
	{
		throw std::domain_error("Strategy '" + strategyName + "' is not present in file '" + this->getFileName() + "'." + "\n" + groupException.getDetailMsg() + "\n");
	}
	catch(H5::AttributeIException &attributeException)
	{
		throw std::runtime_error("File '" + this->getFileName() + "', group '" + groupLocation + "', some attributes could not be read." + attributeException.getDetailMsg() + "\n");
	}
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
