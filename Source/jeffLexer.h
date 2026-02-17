#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#define TRUTH "true"
#define UNTRUTH "false"
#define CHARMARK '\''
#define STRINGMARK '\"'
#define FLOATMARK 'f'
#define 

class jeffLexer
{
public:
	enum TOKENTYPE
	{
		// special
		ILLEGAL, EndF,
		// user-defined
		ID,
		// demarcations
		LPAR, RPAR, LSEQ, REQ, LBLOCK, RBLOCK,
		// punctuation
		SEQDELIM, DECIMAL, SEMICOLON, COLON, QMARK,
		EOL, ESCAPE,
		// operators
		PLUS, MINUS, TIMES, DIVIDE, EXPONENT, MODULO, FACTORIAL,
		ASSIGN, ASSIGNADD, ASSIGNSUB, ASSIGNMUL, ASSIGNDIV,
		EQUAL, NEQUAL,
		LESS, GREATER, LESSEQ, GREATEREQ,
		INCREMENT, DECREMENT, 
		NOT, AND, NAND, OR, NOR, XOR, XNOR, DOLLAR, DEREF, BACKTICK,
		// keywords
		RETURN, BREAK, CONTINUE,
		IF, ELSE, FOR, WHILE,
		SINT8, SINT16, SINT32, SINT64,
		UINT8, UINT16, UINT32, UINT64,
		FLOAT32, FLOAT64,
		BOOL, CHAR, STRING, ENUM,
		SQRT,
		// literals
		BOOLLITERAL, CHARLITERAL, INTLITERAL, FLOATLITERAL, DOUBLELITERAL, STRINGLITERAL
	};

	// pre-defined tokens
	std::unordered_map<std::string, TOKENTYPE> keywordDictionary =
	{
		{"return", RETURN}, {"break", BREAK}, {"continue", CONTINUE},
		{"if", IF}, {"else", ELSE}, {"for", FOR}, {"while", WHILE},
		{"sint8", SINT8}, {"sint16", SINT16}, {"sint32", SINT32}, {"sint64", SINT64},
		{"uint8", UINT8}, {"uint16", UINT16}, {"uint32", UINT32}, {"uint64", UINT64},
		{"float32", FLOAT32}, {"float64", FLOAT64}, 
		{"bool", BOOL}, {"char", CHAR}, {"string", STRING}, {"enum", ENUM},
		{"sqrt", SQRT}
	};

	std::unordered_map<std::string, TOKENTYPE> multicharDictionary =
	{
		// demarcations
		{"(", LPAR}, {")", RPAR}, {"[", LARRAY}, {"]", RARRAY}, {"{", LBLOCK}, {"}", RBLOCK},
		// punctuation
		{",", COMMA}, {".", DOT}, {";", SEMICOLON}, {"?", QMARK}, {"\\", ESCAPE},
		// operators
		{"&", AND}, {"~&", NAND}, {"~|", NOR}, {"^", EXPONENT}, {"!", FACTORIAL}, {"~", NOT}, {"%", MODULO}, {"$", DOLLAR}, {"#", EOL}, {"@", DEREF}, {"`", BACKTICK}, {"=", EQUAL},
		{":", COLON}, {"+", PLUS}, {"-", MINUS}, {"*", TIMES}, {"/", DIVIDE}, {">", GREATEREQ}, {"<", LESSEQ},
		{":=", ASSIGN}, {"+=", ASSIGNADD}, {"-=", ASSIGNSUB}, {"*=", ASSIGNMUL}, {"/=", ASSIGNDIV},
		{">=", GREATEREQ}, {"<=", LESSEQ}, {"~=", NEQUAL}, 
		{"++", INCREMENT}, {"--", DECREMENT}
	};

	struct jeffToken
	{
		TOKENTYPE type = ILLEGAL;
		std::string lexeme;
	};

	jeffLexer();
	~jeffLexer();

	std::vector<jeffToken> lexify(std::string inputText);

	bool getMultiSymToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken);
	bool getStringToken(std::string inputText, int& readIndex, jeffToken& curToken);

	bool handleCharStringLiteral(std::string inputText, int& readIndex, jeffToken& curToken);
	bool handleNumberLiteral(std::string inputText, int& readIndex, jeffToken& curToken);
	bool handleIdentifier(std::string inputText, int& readIndex, jeffToken& curToken);
};

