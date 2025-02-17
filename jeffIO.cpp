#include "jeffIO.h"

jeffIO::jeffIO()
{

}

jeffIO::~jeffIO()
{

}

std::string jeffIO::readFile(std::string filename)
{
	std::string fileText;

	std::ifstream inputFile;
	inputFile.open(filename.c_str(), std::ios::in);
	assert(inputFile.is_open());

	std::string line;
	while (std::getline(inputFile, line))
	{
		fileText.append(line.append("\n"));
	}

	inputFile.close();

	return fileText;
}