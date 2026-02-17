#pragma once

#include <string>

#define COMMENT '`'

class jeffPreprocessor
{
public:
	jeffPreprocessor();
	~jeffPreprocessor();

	std::string preprocessLine(std::string inputText);
	std::string preprocess(std::string inputText);
};

