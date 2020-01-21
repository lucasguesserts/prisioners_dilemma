#include <PrisonersDilemmaFile.hpp>

PrisonersDilemmaFile::PrisonersDilemmaFile(const char * filePath)
	: H5::H5File(filePath, H5F_ACC_TRUNC)
{
	return;
}

void PrisonersDilemmaFile::save(Championship & championship)
{
	// TODO: add try/catch
	H5::Group group = this->createGroup(championship.name);
	PrisonersDilemmaFile::createAttribute(group, "name"         , championship.name          );
	PrisonersDilemmaFile::createAttribute(group, "description"  , championship.description   );
	PrisonersDilemmaFile::createAttribute(group, "numberOfTurns", championship.numberOfTurns );
	group.close();
	return;
}

void PrisonersDilemmaFile::createAttribute(
	H5::Group   group,
	std::string attributeName,
	std::string attributeData
){
	const hsize_t dims[]    = {1};
	H5::StrType dtype(H5::PredType::C_S1);
	dtype.setSize((attributeData.size()+1)*sizeof(char));
	H5::DataSpace dataspace(1, dims);
	H5::Attribute attribute = group.createAttribute(attributeName.c_str(), dtype, dataspace);
	attribute.write(dtype, attributeData.c_str()); 
	dtype.close();
	dataspace.close();
	attribute.close();
	return;
}

void PrisonersDilemmaFile::createAttribute(
	H5::Group   group,
	std::string attributeName,
	unsigned    attributeValue
){
	const hsize_t dims[]    = {1};
	H5::DataSpace dataspace(1, dims);
	H5::Attribute attribute = group.createAttribute(attributeName.c_str(), H5::PredType::STD_U32LE, dataspace);
	attribute.write(H5::PredType::NATIVE_UINT, &attributeValue); 
	dataspace.close();
	attribute.close();
	return;
}

/*
#include <vector>
#include <H5Cpp.h>

int main()
{
	// File
	std::string fileName = "from_cpp.h5";
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	
	{ // File attribute
		H5std_string  attrName  = "name";
		H5std_string  attrData  = "test file";
		const hsize_t dims[]    = {1};

		H5::StrType dtype(H5::PredType::C_S1);
		dtype.setSize(H5T_VARIABLE);
		H5::DataSpace dataspace(1, dims);
		H5::Attribute attribute = file.createAttribute(attrName, dtype, dataspace);
		attribute.write(dtype, attrData); 
		attribute.close();
		dataspace.close();
	}

	// Writing string attribute with fixed size
	// 
	// H5::AtomType dtype(H5::PredType::C_S1);
	// dtype.setSize(attrData.size()*sizeof(char));
	// H5::DataSpace dataspace(1, dims);
	// H5::Attribute attribute = file.createAttribute(attrName, dtype, dataspace);
	// attribute.write(dtype, attrData); 
	// attribute.close();
	// dataspace.close();

	// Group
	H5::Group group = file.createGroup("group example");

	{ // Group attribute
		H5std_string  attrName  = "number";
		int           attrData  = 3;
		const hsize_t dims[]    = {1};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(1, dims);
		H5::Attribute attribute = group.createAttribute(attrName, dtype, dataspace);
		attribute.write(dtype, &attrData); 
		attribute.close();
		dataspace.close();
	}

	{ // Group dataset
		H5std_string  datasetName = "simple vector";
		std::vector<int> datasetData = {0, 1, 2};
		const hsize_t dims[]    = {3};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(1, dims);
		H5::DataSet dataset = group.createDataSet(datasetName, dtype, dataspace);
		dataset.write(datasetData.data(), H5::PredType::NATIVE_INT);
		dtype.close();
		dataspace.close();
		dataset.close();
	}

	{ // File dataset
		H5std_string  datasetName = "complex vector";
		std::vector<int> datasetData = {0, 1, 2, 0, 10, 20};
		const hsize_t dims[]    = {2, 3};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(2, dims);
		H5::DataSet dataset = file.createDataSet(datasetName, dtype, dataspace);
		dataset.write(datasetData.data(), H5::PredType::NATIVE_INT);
		dtype.close();
		dataspace.close();
		dataset.close();
	}

	// Group with hard liink
	H5::Group groupHL = file.createGroup("something inside");
	groupHL.link(H5L_TYPE_HARD, "/group example", "group with things");

	groupHL.close();
	group.close();
	file.close();
	return 0;
}
*/
