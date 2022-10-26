#include <iostream>
#include <fmt/format.h>
#include "Lex.hpp"
#include "ArgManager.hpp"

using namespace std;
int main()
{
	string type = "type", value = "value";
	cout << fmt::format("{{ type:\"{}\", value: \"{}\" }}", type, value) << endl;

	mini_c::MiniCFlowModel flowModel;
	return 0;
}