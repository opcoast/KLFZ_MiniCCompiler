#pragma once
#include "FlowModel.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace mini_c
{
	using std::string, std::unordered_map;
	using std::vector, std::unordered_set;

	// definitions of charset, id, and dfa states
	const unordered_map<string, string> OP_MAP = {

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
		{"MAKE_TABLE","\t"},

		// Bit Operators
		{"B_AND", "&"},
		{"B_OR", "|"},
		{"B_NOT", "~"},
		{"B_XOR", "^"},
		{"B_LSHIFT", "<<"},
		{"B_RSHIFT", ">>"},


		// Brackets
		{"L_BRACKET", "("},
		{"R_BRACKET", ")"},
		{"L_BRACE", "{"},
		{"R_BRACE", "}"},
		{"L_S_BRACKET", "["},
		{"R_S_BRACKET", "]"},

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

		// MemIO
		{"DOLLAR","$"}
	};

	const unordered_map<string, int> TOKEN_ID = {
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

	const unordered_map<string, int> DFA_STATE_ID = {
		{"RESET", 0},
		{"OPERATOR", 1},
		{"SYMBOL", 2},
		{"F_BIT_AND", 3},
		{"S_BIT_AND", 4},
		{"F_BIT_OR", 5},
		{"S_BIT_OR", 6},
		{"F_GT", 7},
		{"S_GT", 8},
		{"F_LT", 9},
		{"S_LT", 10},
		{"F_NOT", 11},
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
		{"CHAR_ESCAPE",24},
		{"END", 100}
	};

	const unordered_map<string, vector<string>> CHARSET = {
		{
			"OPERATOR", {
				OP_MAP.at("PLUS"), OP_MAP.at("SUBTRACT"), OP_MAP.at("TIMES"),
				OP_MAP.at("DIVIDE"), OP_MAP.at("MODE"), OP_MAP.at("NOT"),
				OP_MAP.at("GT"), OP_MAP.at("LT"), OP_MAP.at("ASSIGN"),
				OP_MAP.at("B_AND"), OP_MAP.at("B_OR"), OP_MAP.at("B_NOT"),
				OP_MAP.at("B_XOR"),OP_MAP.at("DOLLAR")
			},
		},
		{
			"SYMBOL", {
				OP_MAP.at("L_BRACKET"), OP_MAP.at("R_BRACKET"), OP_MAP.at("L_BRACE"),
				OP_MAP.at("R_BRACE"), OP_MAP.at("L_S_BRACKET"), OP_MAP.at("R_S_BRACKET"),
				OP_MAP.at("DOT"), OP_MAP.at("COMMA"), OP_MAP.at("SEMICOLON"),
				OP_MAP.at("QUOTATION"), OP_MAP.at("D_QUOTATION"), OP_MAP.at("SHARP"),
				OP_MAP.at("QUESTION"), OP_MAP.at("COLON")
			}
		},
		{
			"SPACE", {
				OP_MAP.at("SPACE"),OP_MAP.at("MAKE_TABLE")
			}
		},
		{
			"NEWLINE", {
				OP_MAP.at("NEWLINE")
			}
		},
		{
			// >= <= == != && || << >>
			"DOUBLE_CHAR", {
				OP_MAP.at("GE"), OP_MAP.at("LE"), OP_MAP.at("EQ"),
				OP_MAP.at("NE"), OP_MAP.at("L_AND"), OP_MAP.at("L_OR"),
				OP_MAP.at("B_LSHIFT"), OP_MAP.at("B_RSHIFT")
			}
		},
		// &&
		{"F_BIT_AND", {OP_MAP.at("B_AND")}},
		{"S_BIT_AND", {OP_MAP.at("B_AND")}},
		// ||
		{"F_BIT_OR", {OP_MAP.at("B_OR")}},
		{"S_OR", {OP_MAP.at("B_OR")}},
		// >>
		{"F_GT", {OP_MAP.at("GT")}},
		{"S_GT", {OP_MAP.at("GT")}},
		// <<
		{"F_LT", {OP_MAP.at("LT")}},
		{"S_LT", {OP_MAP.at("LT")}},
		// >= <= != ==
		{"F_NOT", {OP_MAP.at("NOT")}},
		{"F_ASSIGN", {OP_MAP.at("ASSIGN")}},
		{"S_ASSIGN", {OP_MAP.at("ASSIGN")}},

		{
			"KEYWORD", {
				"char", "int", "long", "float", "double", "sizeof", "signed", "unsigned",
				"if", "else", "while", "for", "do", "break", "continue", "goto", "main",
				"void", "return", "switch", "case", "default",
				"const", "static", "auto", "extern", "register",
				"struct", "union", "enum", "typedef",
				"include",
			}
		}

	};

	const unordered_map<string, int> DFA_STATE = {
		// reset
		{"RESET", DFA_STATE_ID.at("RESET")},
		// operator and symbol
		{"OPERATOR", DFA_STATE_ID.at("OPERATOR")},
		{"SYMBOL", DFA_STATE_ID.at("SYMBOL")},

		// && || >> << >= <= != ==
		{"F_BIT_AND", DFA_STATE_ID.at("F_BIT_AND")},
		{"S_BIT_AND", DFA_STATE_ID.at("S_BIT_AND")},
		{"F_BIT_OR", DFA_STATE_ID.at("F_BIT_OR")},
		{"S_BIT_OR", DFA_STATE_ID.at("S_BIT_OR")},
		{"F_GT", DFA_STATE_ID.at("F_GT")},
		{"S_GT", DFA_STATE_ID.at("S_GT")},
		{"F_LT", DFA_STATE_ID.at("F_LT")},
		{"S_LT", DFA_STATE_ID.at("S_LT")},
		{"F_NOT", DFA_STATE_ID.at("F_NOT")},
		{"F_ASSIGN", DFA_STATE_ID.at("F_ASSIGN")},
		{"S_ASSIGN", DFA_STATE_ID.at("S_ASSIGN")},

		// space newline identifier
		{"SPACE", DFA_STATE_ID.at("SPACE")},
		{"NEWLINE", DFA_STATE_ID.at("NEWLINE")},
		{"IDENTIFIER", DFA_STATE_ID.at("IDENTIFIER")},

		// number float string char
		{"NUMBER", DFA_STATE_ID.at("NUMBER")},
		{"FLOAT", DFA_STATE_ID.at("FLOAT")},
		{"STRING", DFA_STATE_ID.at("STRING")},
		{"STRING_ESCAPE", DFA_STATE_ID.at("STRING_ESCAPE")},
		{"STRING_END", DFA_STATE_ID.at("STRING_END")},
		{"CHAR", DFA_STATE_ID.at("CHAR")},
		{"CHAR_END", DFA_STATE_ID.at("CHAR_END")},
		{"CHAR_ESCAPE", DFA_STATE_ID.at("CHAR_ESCAPE")},

		// end
		{"END", DFA_STATE_ID.at("END")},
	};

	// definitions of utils functions
	bool isInArr(const string& val, const vector<string>& arr)
	{
		return std::find(arr.begin(), arr.end(), val) != arr.end();
	}

	string getTokenType(const string& token)
	{
		if (isInArr(token, CHARSET.at("OPERATOR")))
			return "Operator";
		if (isInArr(token, CHARSET.at("DOUBLE_CHAR")))
			return "DoubleOperator";
		if (isInArr(token, CHARSET.at("SYMBOL")))
			return "Symbol";
		if (isInArr(token, CHARSET.at("KEYWORD")))
			return "Keyword";
		return "";
	}

	string getTokenType(int state, const string& token)
	{
		string tokenType = getTokenType(token);
		if (!tokenType.empty())
			return tokenType;
		if (state == DFA_STATE.at("SPACE"))
			return "SPACE";
		if (state == DFA_STATE.at("NEWLINE"))
			return "NEWLINE";
		if (state == DFA_STATE.at("IDENTIFIER"))
			return "Identifier";
		if (state == DFA_STATE.at("NUMBER"))
			return "Number";
		if (state == DFA_STATE.at("FLOAT"))
			return "Float";
		if (state == DFA_STATE.at("STRING_END"))
			return "String";
		if (state == DFA_STATE.at("CHAR_END"))
			return "Char";
		return "UNKNOWN";
	}

	int getFirsetCharState(const string& ch)
	{
		if (isInArr(ch, CHARSET.at("F_BIT_AND")))
			return DFA_STATE.at("F_BIT_AND");
		if (isInArr(ch, CHARSET.at("F_BIT_OR")))
			return DFA_STATE.at("F_BIT_OR");
		if (isInArr(ch, CHARSET.at("F_GREAT")))
			return DFA_STATE.at("F_GT");
		if (isInArr(ch, CHARSET.at("F_LESS")))
			return DFA_STATE.at("F_LT");
		if (isInArr(ch, CHARSET.at("F_NOT")))
			return DFA_STATE.at("F_NOT");
		if (isInArr(ch, CHARSET.at("F_ASSIGN")))
			return DFA_STATE.at("F_ASSIGN");
		return DFA_STATE.at("RESET");
	}

	int getSecondCharState(const string& ch)
	{
		if (isInArr(ch, CHARSET.at("S_BIT_AND")))
			return DFA_STATE.at("S_BIT_AND");
		if (isInArr(ch, CHARSET.at("S_BIT_OR")))
			return DFA_STATE.at("S_BIT_OR");
		if (isInArr(ch, CHARSET.at("S_GREAT")))
			return DFA_STATE.at("S_GT");
		if (isInArr(ch, CHARSET.at("S_LESS")))
			return DFA_STATE.at("S_LT");
		if (isInArr(ch, CHARSET.at("S_ASSIGN")))
			return DFA_STATE.at("S_ASSIGN");
		return DFA_STATE.at("RESET");
	}

	bool isOperatorChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("OPERATOR"));
	}

	bool isSymbolChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("SYMBOL"));
	}

	bool isSpaceChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("SPACE"));
	}

	bool isNewlineChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("NEWLINE"));
	}

	bool isFirstChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("F_BIT_AND")) ||
			isInArr(ch, CHARSET.at("F_BIT_OR")) ||
			isInArr(ch, CHARSET.at("F_GREAT")) ||
			isInArr(ch, CHARSET.at("F_LESS")) ||
			isInArr(ch, CHARSET.at("F_NOT")) ||
			isInArr(ch, CHARSET.at("F_ASSIGN"));
	}

	bool isSecondChar(const string& ch)
	{
		return isInArr(ch, CHARSET.at("S_BIT_AND")) ||
			isInArr(ch, CHARSET.at("S_BIT_OR")) ||
			isInArr(ch, CHARSET.at("S_GREAT")) ||
			isInArr(ch, CHARSET.at("S_LESS")) ||
			isInArr(ch, CHARSET.at("S_ASSIGN"));
	}

	bool isAlphabetChar(const string& ch)
	{
		char c = ch[0];
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}

	bool isNumberChar(const string& ch)
	{
		char c = ch[0];
		return c >= '0' && c <= '9';
	}

	bool isInStates(const int& state, const vector<int>& states)
	{
		return std::find(states.begin(), states.end(), state) != states.end();
	}

	bool isFirstCharOfDoubleChar(const string& ch) {
		return isFirstChar(ch);
	}

	bool isSecondCharOfDoubleChar(const string& ch) {
		return isSecondChar(ch);
	}
	
	struct MiniCFlowModel :public FlowModel {
		vector<path> resultPaths = {};

		void pathGrow(const path& path)
		{
			resultPaths.push_back(path);
		}

		void toDefault()
		{
			resultPaths.clear();
		}

		int getNextState(const string& ch, int state, vector<string>& matches)
		{
			// handling string
			if (isInStates(state, { DFA_STATE.at("STRING"),DFA_STATE.at("STRING_ESCAP") }))
			{
				if (state == DFA_STATE.at("STRING") && ch == OP_MAP.at("ESCAPE"))
					return DFA_STATE.at("STRING_ESCAPE");
				if (state == DFA_STATE.at("STRING_ESCAPE"))
					return DFA_STATE.at("STRING");
				if (ch != OP_MAP.at("D_QUOTATION"))
					return DFA_STATE.at("STRING");
				else
					return DFA_STATE.at("STRING_END");
			}

			// handling char
			if (isInStates(state, { DFA_STATE.at("CHAR"),DFA_STATE.at("CHAR_ESCAPE") }))
			{
				if (matches.size() == 1)
				{
					if (ch == OP_MAP.at("ESCAPE"))
						return DFA_STATE.at("CHAR_ESCAPE");
					else
						return DFA_STATE.at("CHAR");
				}
				else if (matches.size() == 2)
				{
					if (matches[1] == OP_MAP.at("ESCAPE"))
						return DFA_STATE.at("CHAR");
					if (ch == OP_MAP.at("QUOTATION"))
						return DFA_STATE.at("CHAR_END");
				}
				else if (matches.size() == 3
					and matches[1] == OP_MAP.at("ESCAPE")
					and ch == OP_MAP.at("QUOTATION"))
				{
					return DFA_STATE.at("CHAR_END");
				}
			}

			// others
			if (isAlphabetChar(ch)) {
				if (isInStates(state, { DFA_STATE.at("RESET") , DFA_STATE.at("IDENTIFIER") })) {
					return DFA_STATE.at("IDENTIFIER");
				}
			}

			// integers and floats
			else if (isNumberChar(ch)) {
				if (isInStates(state, { DFA_STATE.at("RESET"),DFA_STATE.at("NUMBER") }))
					return DFA_STATE.at("NUMBER");
				if (isInStates(state, { DFA_STATE.at("FLOAT") }))
					return DFA_STATE.at("FLOAT");
				if (isInStates(state, { DFA_STATE.at("IDENTIFIER") }))
					return DFA_STATE.at("IDENTIFIER");
			}

			// operators
			else if (isOperatorChar(ch)) {
				if (isFirstCharOfDoubleChar(ch)) {
					if (isInStates(state, { DFA_STATE.at("RESET") }))
						return getFirsetCharState(ch);
				}
				if (isSecondCharOfDoubleChar(ch)) {
					if (state == DFA_STATE.at("F_BIT_AND")
						and ch == OP_MAP.at("B_AND"))
						return DFA_STATE.at("S_BIT_AND");
					if (state == DFA_STATE.at("F_BIT_OR")
						and ch == OP_MAP.at("B_OR"))
						return DFA_STATE.at("S_BIT_OR");
					if (state == DFA_STATE.at("F_GT")
						and ch == OP_MAP.at("GT"))
						return DFA_STATE.at("S_GT");
					if (state == DFA_STATE.at("F_LT")
						and ch == OP_MAP.at("LT"))
						return DFA_STATE.at("S_LT");

					if (isInStates(state, {
						DFA_STATE.at("F_GT"),
						DFA_STATE.at("F_LT"),
						DFA_STATE.at("F_NOT"),
						DFA_STATE.at("F_ASSIGN")
						}) and ch == OP_MAP.at("ASSIGN"))
						return DFA_STATE.at("S_ASSIGN");

				}
				if (state == DFA_STATE.at("RESET"))
					return DFA_STATE.at("OPERATOR");
			}

			// symbol
			else if (isSymbolChar(ch)) {
				if (isInStates(state, { DFA_STATE.at("RESET") })) {
					if (ch == OP_MAP.at("QUOTATION"))
						return DFA_STATE.at("CHAR");
					if (ch == OP_MAP.at("D_QUOTATION"))
						return DFA_STATE.at("STRING");
					return DFA_STATE.at("SYMBOL");
				}
				if (state == DFA_STATE.at("NUMBER") and ch == OP_MAP.at("DOT"))
					return DFA_STATE.at("FLOAT");
			}

			// white space
			else if (isSpaceChar(ch)) {
				if (state == DFA_STATE.at("RESET"))
					return DFA_STATE.at("SPACE");
			}

			// new line
			else if (isNewlineChar(ch)) {
				if (state == DFA_STATE.at("RESET"))
					return DFA_STATE.at("NEWLINE");
			}

			// id
			else if (isInStates(state, { DFA_STATE.at("RESET"),DFA_STATE.at("IDENTIFIER") }))
			{
				return DFA_STATE.at("IDENTIFIER");
			}

			// reset
			return DFA_STATE.at("RESET");
		}
	};

}