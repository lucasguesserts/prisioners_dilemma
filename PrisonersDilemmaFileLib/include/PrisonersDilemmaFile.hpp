#ifndef PRISONERS_DILEMMA_FILE_HPP
#define PRISONERS_DILEMMA_FILE_HPP

#include <H5Cpp.h>
#include <string>
#include <Championship.hpp>

class PrisonersDilemmaFile: public H5::H5File
{
	public:
		PrisonersDilemmaFile(std::string filePath, int flags=H5F_ACC_TRUNC);

		void save(Championship &);
		Championship load(std::string champioshipName);

	private:
		static void createAttribute(H5::Group group, std::string attributeName, std::string attributeData);
		static void createAttribute(H5::Group group, std::string attributeName, unsigned attributeValue  );
		static std::string loadStrAttribute(H5::Group group, std::string attributeName);
		static unsigned loadUnsignedAttribute(H5::Group group, std::string attributeName);
};

#endif
