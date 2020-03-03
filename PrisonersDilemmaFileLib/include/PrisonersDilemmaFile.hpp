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

namespace PrisonersDilemma
{

	class File: public H5::H5File
	{
		public:
			// TODO: fix error, when 'flags' is not included in the
			// parameters, there will be an error:
			//     error while loading shared libraries: libhdf5.so.103:
			//     cannot open shared object file: No such file or directory
			// Fix it!
			File(const std::string & filePath, const unsigned flags=H5F_ACC_RDONLY);
			File(const std::string & filePath, const Championship & championship, const unsigned flags=H5F_ACC_TRUNC);
			static const std::string strategiesGroupName;

		private:
			void save(const Championship &                  ) const;
			void save(const Strategy * const                ) const;
			void save(const H5::Group &     , const Player &) const;

			// TODO: those functions receive a lot of parameters and
			// they do a lot of things. Correct it.
			H5::Group getStrategiesGroup(void) const;
			void        savePlayerData(const H5::Group & championshipGroup, const H5::Group & playerGroup, const std::vector<Decision> & decision, const std::vector<Payoff> & payoff, const Strategy * const partnerStrategy) const;
			static void saveAttribute (const H5::Group & group, const std::string & attributeName, const std::string & attributeData);
			static void saveAttribute (const H5::Group & group, const std::string & attributeName, const unsigned attributeValue  );

#ifdef PUBLIC_TEST_METHODS
		public:
#else
		private:
#endif
			static std::string           loadStrAttribute     (const H5::Group & group, const std::string & attributeName);
			static unsigned              loadUnsignedAttribute(const H5::Group & group, const std::string & attributeName);
			static std::vector<Decision> loadDecisions        (const H5::Group & group, const unsigned      numberOfTurns);
			static std::vector<Payoff>   loadPayoff           (const H5::Group & group, const unsigned      numberOfTurns);
	};

}

#endif
