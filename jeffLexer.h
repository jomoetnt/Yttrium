#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class jeffLexer
{
public:
	enum TOKENTYPE
	{
		ILLEGAL,
		DIGIT,
		ID,
		LPAR,
		RPAR,
		LBRACKET,
		RBRACKET,
		LBRACE,
		RBRACE,
		COMMA,
		DOT,
		SEMICOLON,
		COLON,
		QUOTE,
		DQUOTE,
		FSLASH,
		BSLASH,
		PLUS,
		MINUS,
		ASSIGN,
		ASSIGNADD,
		ASSIGNSUB,
		ASSIGNMUL,
		ASSIGNDIV,
		EQUAL,
		NEQUAL,
		LESS,
		GREATER,
		LESSEQ,
		GREATEREQ,
		INCREMENT,
		DECREMENT,
		ASTERISK,
		AMPERSAND,
		PIPE,
		CARAT,
		PERCENT,
		EXMARK,
		QMARK,
		TRUE,
		FALSE,
		RETURN,
		IF,
		ELSE,
		SINT8,
		SINT16,
		SINT32,
		SINT64,
		UINT8,
		UINT16,
		UINT32,
		UINT64,
		FLOAT,
		DOUBLE,
		BOOL,
		CHAR,
		STRING,
		CHARLITERAL,
		STRINGLITERAL
	};

	// alphanumeric character string tokens
	std::unordered_map<std::string, TOKENTYPE> dictionary =
	{
		{"true", TRUE},
		{"false", FALSE},
		{"return", RETURN},
		{"if", IF},
		{"else", ELSE},
		{"sint8", SINT8},
		{"sint16", SINT16},
		{"sint32", SINT32},
		{"sint64", SINT64},
		{"uint8", UINT8},
		{"uint16", UINT16},
		{"uint32", UINT32},
		{"uint64", UINT64},
		{"float", FLOAT},
		{"double", DOUBLE},
		{"bool", BOOL},
		{"char", CHAR},
		{"string", STRING}
	};

	struct jeffToken
	{
		TOKENTYPE type = ILLEGAL;
		std::string lexeme;
	};

	jeffLexer();
	~jeffLexer();

	std::vector<jeffToken> lexify(std::string inputText);

	bool getCharToken(char curChar, jeffToken& curToken);
	bool getMultiSymToken(std::string inputText, int& readIndex, jeffToken& curToken);
	bool getStringToken(std::string inputText, int& readIndex, jeffToken& curToken);
};

