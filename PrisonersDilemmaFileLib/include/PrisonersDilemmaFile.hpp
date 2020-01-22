#ifndef PRISONERS_DILEMMA_FILE_HPP
#define PRISONERS_DILEMMA_FILE_HPP

#include <H5Cpp.h>
#include <string>
#include <Championship.hpp>
#include <Strategies.hpp>

class PrisonersDilemmaFile: public H5::H5File
{
	public:
		PrisonersDilemmaFile(std::string filePath, int flags=H5F_ACC_TRUNC);

		void save(Championship &);
		void save(Strategy *);
		Championship load(std::string champioshipName);
		Strategy*    loadStrategy(std::string strategyName);

		static const std::string strategiesGroup;

	private:
		H5::Group getStrategiesGroup(void);
		static void saveAttribute(H5::Group group, std::string attributeName, std::string attributeData);
		static void saveAttribute(H5::Group group, std::string attributeName, unsigned attributeValue  );
		static std::string loadStrAttribute(H5::Group group, std::string attributeName);
		static unsigned loadUnsignedAttribute(H5::Group group, std::string attributeName);
};

#endif
