#include <iostream>
#include <fmt/format.h>
#include "Lex.hpp"
#include "ArgManager.hpp"

using namespace std;
int main()
{
	string stream = R"(
int main(){
char '\b';
$0x0001 = 0XfFfF;
cout << "Hello World" << endl;
return 0;
}
)";
	lexer::start(stream);
	for (auto& token : lexer::DFA::result.tokens) {
		cout << token.toString() << endl;
	}
	return 0;
}