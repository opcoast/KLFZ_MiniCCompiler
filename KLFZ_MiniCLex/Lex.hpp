#pragma once
#include "FlowModel.hpp"
#include <regex>

// Input stream reader
namespace lexer {
	using std::string;
	// Input stream reader
	namespace ISR {
		struct ISR_props {
			string stream = "";
			int length = 0;
			int seq = 0;
		} props;

		void incSeq() { props.seq++; }

		void toDefault()
		{
			props.stream = "";
			props.length = 0;
			props.seq = 0;
		}
		void before(string& stream)
		{
			props.stream = string(stream);
			// Ìæ»»¶àÓàµÄ»»ÐÐ·û
			props.stream =
				std::regex_replace(props.stream, std::regex("\n+"), "\n");
			// É¾³ýÐÐ×¢ÊÍºÍ¿é×¢ÊÍ
			props.stream =
				std::regex_replace(props.stream, std::regex(R"(\/\/[^\n]*)"), "\n");
			props.stream =
				std::regex_replace(props.stream, std::regex(R"(\/\*(\s|.)*?\*\/)"), " ");
			// trim stream
			if (!props.stream.empty()) {
				props.stream.erase(0, props.stream.find_first_not_of(" \t\r\n"));
				props.stream.erase(props.stream.find_last_not_of(" \t\r\n") + 1);
			}
			props.seq = 0;
			props.length = stream.length();
		}
		void after()
		{

		}
	}

	namespace DFA {
		int state;
	}
}