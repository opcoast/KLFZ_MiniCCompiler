#pragma once
#include "Lex.hpp"
#include <string>

class Lexer
{
public:
	Lexer();
	~Lexer();
	void start(const std::string&);
};



class LexerFactory
{
public:
	LexerFactory(const std::string& mod);
private:
	LexerFactory();
	~LexerFactory();
};

LexerFactory::LexerFactory(const std::string& mod) {

}