#include "MiniC.h"

namespace MiniC
{
	using std::string, std::unordered_map, std::unordered_set;

	unordered_map<string, string> CHAR_MAP = {

		// Math operators
		{"PLUS", "+"},
		{"SUBTRACT", "-"},
		{"TIMES", "*"},
		{"DIVIDE", "/"},
		{"MODE", "%"},

		// Logical Operators
		{"NOT", "!"},
		{"L_AND", "&&"},
		{"L_OR", "||"},

		// Compare Operator
		{"GT", ">"},
		{"LT", "<"},
		{"EQ", "=="},
		{"ASSIGN", "="},
		{"GE", ">="},
		{"LE", "<="},
		{"NE", "!="},

		// Space
		{"SPACE", " "},
		{"NEWLINE", "\n"},

		// Bit Operators
		// TODO


		// Brackets
		{"L_BRACKET", "("},
		{"R_BRACKET", ")"},
		{"L_BRACE", "{"},
		{"R_BRACE", "}"},
		{"L_S_BRACKET", "("},
		{"R_S_BRACKET", ")"},

		// SEPARATORS
		{"DOT", "."},
		{"COMMA", ","},
		{"SEMICOLON", ";"},
		{"QUOTATION", "'"},
		{"D_QUOTATION", "\""},
		{"QUESTION", "?"},
		{"SHARP", "#"},
		{"COLON", ":"},
		{"ESCAPE", "\\"},
	};

	unordered_map<string, int> TOKEN_ID = {
		{"OPERATOR", 1},
		{"D_OPERATOR", 2},
		{"SYMBOL", 3},
		{"SPACE", 4},
		{"NEWLINE", 5},
		{"KEYWORD", 6},
		{"IDENTIFIER", 7},
		{"NUMBER", 8},
		{"FLOAT", 9},
		{"STRING", 10},
		{"CHAR", 11},
		{"UNKNOWN", 12}
	};

	unordered_map<string, int> DFA_STATE_ID = {
		{"RESET", 0},
		{"OPERATOR", 1},
		{"SYMBOL", 2},
		{"F_BIT_AND", 3},
		{"S_BIT_AND", 4},
		{"F_BIT_OR", 5},
		{"S_BIT_OR", 6},
		{"F_GE", 7},
		{"S_GE", 8},
		{"F_LE", 9},
		{"S_LE", 10},
		{"NOT", 11},
		{"F_ASSIGN", 12},
		{"S_ASSIGN", 13},
		{"SPACE", 14},
		{"NEWLINE", 15},
		{"IDENTIFIER", 16},
		{"NUMBER", 17},
		{"FLOAT", 18},
		{"STRING", 19},
		{"STRING_ESCAPE", 20},
		{"STRING_END", 21},
		{"CHAR", 22},
		{"CHAR_END", 23},
		{"END", 100}
	};
}
