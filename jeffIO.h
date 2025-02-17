#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

class jeffIO
{
public:
	jeffIO();
	~jeffIO();
	std::string readFile(std::string filename);
};

