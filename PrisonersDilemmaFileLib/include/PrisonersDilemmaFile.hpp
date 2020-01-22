#ifndef PRISONERS_DILEMMA_FILE_HPP
#define PRISONERS_DILEMMA_FILE_HPP

#include <H5Cpp.h>
#include <string>
#include <Championship.hpp>

class PrisonersDilemmaFile: public H5::H5File
{
	public:
		PrisonersDilemmaFile(std::string filePath);

		void save(Championship &);

	private:
		static void createAttribute(H5::Group group, std::string attributeName, std::string attributeData);
		static void createAttribute(H5::Group group, std::string attributeName, unsigned attributeValue  );
};

#endif
