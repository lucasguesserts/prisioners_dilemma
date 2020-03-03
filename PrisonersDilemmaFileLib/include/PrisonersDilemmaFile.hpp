#ifndef PRISONERS_DILEMMA_FILE_HPP
#define PRISONERS_DILEMMA_FILE_HPP

#include "H5Cpp.h"
#include <string>
#include <vector>
#include "Decision.hpp"
#include "Payoff.hpp"
#include "Strategy.hpp"
#include "Strategies.hpp"
#include "Player.hpp"
#include "Championship.hpp"

class PrisonersDilemmaFile: public H5::H5File
{
	public:
		PrisonersDilemmaFile(const std::string & filePath, const unsigned flags=H5F_ACC_RDONLY);
		PrisonersDilemmaFile(const std::string & filePath, const Championship & championship);

		void save(const Championship &                  ) const;
		void save(const Strategy * const                ) const;
		void save(const H5::Group &     , const Player &) const;

		static const std::string strategiesGroupName;

	private:
		// TODO: those functions receive a lot of parameters and
		// they do a lot of things. Correct it.
		void savePlayerData(const H5::Group & championshipGroup, const H5::Group & playerGroup, const std::vector<Decision> & decision, const std::vector<Payoff> & payoff, const Strategy * const partnerStrategy) const;
		H5::Group getStrategiesGroup(void) const;
		static void saveAttribute(const H5::Group & group, const std::string & attributeName, const std::string & attributeData);
		static void saveAttribute(const H5::Group & group, const std::string & attributeName, const unsigned attributeValue  );
		static std::string loadStrAttribute(const H5::Group & group, const std::string & attributeName);
		static unsigned loadUnsignedAttribute(const H5::Group & group, const std::string & attributeName);
};

#endif
