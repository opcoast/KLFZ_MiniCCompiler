#pragma once
#include <vector>
#include <string>
#include <fmt/core.h>
#include <regex>

namespace MiniCLex 
{
	struct Path {
		int state;
		std::string ch;
		int nextState;
		bool match;
		bool end;
	};

	struct token {
		std::string type;
		std::string value;
		std::string toString() {
			value = std::regex_replace(value, std::regex("\""), "\\\"");
			return fmt::format("{{ \"type\":\"{}\", \"value\": \"{}\" }}", type, value);
		}
	};

	struct FlowModel {
		std::vector<Path> resultPaths;
		virtual void pathGrow(const Path& Path) = 0;
		virtual void toDefault() = 0;
		virtual int getNextState(
			const std::string& ch,
			int state, std::vector<std::string>& matches
		) = 0;
	};
}

