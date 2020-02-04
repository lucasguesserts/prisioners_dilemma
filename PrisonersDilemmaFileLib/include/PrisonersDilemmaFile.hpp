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
		PrisonersDilemmaFile(std::string filePath, unsigned flags=H5F_ACC_TRUNC);

		void save(Championship &);
		void save(Strategy *);
		void save(H5::Group &, Player &);

		static const std::string strategiesGroupName;

	private:
		void savePlayerData(H5::Group championshipGroup, H5::Group playerGroup, std::vector<Decision> decision, std::vector<Payoff> payoff, Strategy * partnerStrategy);
		H5::Group getStrategiesGroup(void);
		static void saveAttribute(H5::Group group, std::string attributeName, std::string attributeData);
		static void saveAttribute(H5::Group group, std::string attributeName, unsigned attributeValue  );
		static std::string loadStrAttribute(H5::Group group, std::string attributeName);
		static unsigned loadUnsignedAttribute(H5::Group group, std::string attributeName);
};

#endif
