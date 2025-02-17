
#include <iostream>
#include "jeffIO.h"
#include "jeffLexer.h"

int main()
{
    jeffIO jefio;
    std::string test = jefio.readFile("test.txt");

    jeffLexer lex;
    std::vector<jeffLexer::jeffToken> tokens = lex.lexify(test);

    std::cout << test;
}
