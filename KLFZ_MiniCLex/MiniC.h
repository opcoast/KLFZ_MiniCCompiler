#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
using std::string, std::unordered_map, std::unordered_set;

namespace MiniC
{
public:
	static unordered_map<string, string> CHAR_MAP;
	static unordered_map<string, int> TOKEN_ID;
	static unordered_map<string, int> DFA_STATE_ID;
};

}