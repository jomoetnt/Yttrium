#include "jeffPreprocessor.h"

jeffPreprocessor::jeffPreprocessor()
{

}

jeffPreprocessor::~jeffPreprocessor()
{

}

std::string jeffPreprocessor::preprocessLine(std::string inputText)
{
	std::string outputText = inputText;

	size_t commentLoc = inputText.find(COMMENT);
	if (commentLoc != std::string::npos)
	{
		outputText = inputText.substr(0, commentLoc);
	}
	return outputText;
}

std::string jeffPreprocessor::preprocess(std::string inputText)
{
	std::string outputText = inputText;

	// search for start of comment block
	for (size_t commentLoc = 0; commentLoc < inputText.length(); commentLoc = inputText.find(COMMENT, commentLoc + 1))
	{
		if (inputText[commentLoc + 1] == COMMENT)
		{
			// search for end of comment block
			for (size_t endCommentLoc = commentLoc + 2; endCommentLoc < inputText.length(); endCommentLoc = inputText.find(COMMENT, endCommentLoc + 1))
			{
				if (inputText[endCommentLoc + 1] == COMMENT)
				{
					outputText = inputText.replace(commentLoc, endCommentLoc + 2 - commentLoc, "");
				}
			}
		}
	}
	return outputText;
}