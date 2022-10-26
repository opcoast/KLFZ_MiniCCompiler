#include <iostream>
#include <fmt/format.h>
#include "Lexer.hpp"
#include "ArgManager.hpp"

using namespace std;
int main(int argc, char** argv)
{
	Lexer* lexer;
	lexer = LexerFactory("network");
	lexer->start();
	return 0;
}