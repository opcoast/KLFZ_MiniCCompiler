#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
namespace mini_c
{
	using std::string, std::unordered_map, std::unordered_set;
	extern const unordered_map<string, string> OP_MAP;
	extern const unordered_map<string, int> TOKEN_ID;
	extern const unordered_map<string, int> DFA_STATE_ID;
};