#include "jeffLexer.h"

jeffLexer::jeffLexer()
{

}

jeffLexer::~jeffLexer()
{

}

std::vector<jeffLexer::jeffToken> jeffLexer::lexify(std::string inputText)
{
	std::vector<jeffToken> tokens;
	for (int readIndex = 0; readIndex < inputText.length(); readIndex++)
	{
		if (std::isspace(inputText[readIndex]))
			continue;

		// determine token at readIndex
		jeffToken curToken;
		if (!getCharToken(inputText[readIndex], curToken))
		{
			if (!getMultiSymToken(inputText, readIndex, curToken))
			{
				if (!getStringToken(inputText, readIndex, curToken))
				{
					curToken.type = ILLEGAL;
				}
			}
		}

		tokens.emplace_back(curToken);
	}
	return tokens;
}

// assigns type to current token and returns true if it is a single character, otherwise returns false
bool jeffLexer::getCharToken(char curChar, jeffLexer::jeffToken& curToken)
{
	switch (curChar)
	{
	case '(':
		curToken.type = LPAR;
		break;
	case ')':
		curToken.type = RPAR;
		break;
	case '{':
		curToken.type = LBRACE;
		break;
	case '}':
		curToken.type = RBRACE;
		break;
	case '[':
		curToken.type = LBRACKET;
		break;
	case ']':
		curToken.type = RBRACKET;
		break;
	case '\\':
		curToken.type = BSLASH;
		break;
	case ';':
		curToken.type = SEMICOLON;
		break;
	case ',':
		curToken.type = COMMA;
		break;
	case '.':
		curToken.type = DOT;
		break;
	case '?':
		curToken.type = QMARK;
		break;
	case '^':
		curToken.type = CARAT;
		break;
	case '%':
		curToken.type = PERCENT;
		break;
	case '|':
		curToken.type = PIPE;
		break;
	case '&':
		curToken.type = AMPERSAND;
		break;
	default:
		return false;
	}
	return true;
}

// assigns type to current token and returns true if it is multiple symbols (i.e., not characters or digits), otherwise returns false
bool jeffLexer::getMultiSymToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	switch (inputText[readIndex])
	{
	case '!':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = NEQUAL;
			readIndex++;
		}
		else
			curToken.type = EXMARK;
		break;
	case ':':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = ASSIGN;
			readIndex++;
		}
		else
			curToken.type = COLON;
		break;
	case '=':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = EQUAL;
			readIndex++;
		}
		else
			curToken.type = ILLEGAL;
		break;
	case '+':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = ASSIGNADD;
			readIndex++;
		}
		else if (inputText[readIndex + 1] == '+')
		{
			curToken.type = INCREMENT;
			readIndex++;
		}
		else
			curToken.type = PLUS;
		break;
	case '-':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = ASSIGNSUB;
			readIndex++;
		}
		else if (inputText[readIndex + 1] == '-')
		{
			curToken.type = DECREMENT;
			readIndex++;
		}
		else
			curToken.type = MINUS;
		break;
	case '*':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = ASSIGNMUL;
			readIndex++;
		}
		else
			curToken.type = ASTERISK;
		break;
	case '/':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = ASSIGNDIV;
			readIndex++;
		}
		else
			curToken.type = FSLASH;
		break;
	case '<':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = LESSEQ;
			readIndex++;
		}
		else
			curToken.type = LESS;
		break;
	case '>':
		if (inputText[readIndex + 1] == '=')
		{
			curToken.type = GREATEREQ;
			readIndex++;
		}
		else
			curToken.type = GREATER;
		break;
	default:
		return false;
	}
	return true;
}

// assigns type to current token and returns true if it is an alphanumeric token, otherwise returns false
bool jeffLexer::getStringToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	// handle char/string literals
	// TODO: handle error if unclosed quote
	if (inputText[readIndex] == '\'')
	{
		readIndex++;
		curToken.type = CHARLITERAL;
		for (; inputText[readIndex] != '\''; readIndex++)
		{
			curToken.lexeme.push_back(inputText[readIndex]);
		}
		return true;
	}
	else if (inputText[readIndex] == '"')
	{
		readIndex++;
		curToken.type = STRINGLITERAL;
		for (; inputText[readIndex] != '"'; readIndex++)
		{
			curToken.lexeme.push_back(inputText[readIndex]);
		}
		return true;
	}

	// identifiers must start with a letter, but can contain numbers after
	if (!std::isalpha(inputText[readIndex]))
		return false;

	std::string tokenName;
	for (; std::isalnum(inputText[readIndex]) || inputText[readIndex] == '_'; readIndex++)
	{
		tokenName.push_back(inputText[readIndex]);
	}
	readIndex--;

	// keywords
	if (dictionary.find(tokenName) != dictionary.end())
	{
		curToken.type = dictionary[tokenName];
	}
	// other identifiers
	else
	{
		curToken.type = ID;
		curToken.lexeme = tokenName;
	}
	return true;
}
