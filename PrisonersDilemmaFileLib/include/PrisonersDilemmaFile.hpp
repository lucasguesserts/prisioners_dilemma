#ifndef PRISONERS_DILEMMA_FILE_HPP
#define PRISONERS_DILEMMA_FILE_HPP

#include <H5Cpp.h>
#include <string>

class PrisonersDilemmaFile: public H5::H5File
{
	public:
		PrisonersDilemmaFile(const std::string &filePath);
};

#endif
