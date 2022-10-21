#pragma once
#include <vector>
#include <string>
#include <fmt/core.h>

struct path {
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
		return fmt::format("{{ type:\"{}\", value: \"{}\" }}", type, value);
	}
};

struct FlowModel {
	std::vector<path> resultPaths;
	virtual void pathGrow(const path& path) = 0;
	virtual void toDefault() = 0;
	virtual int getNextState(
		const std::string& ch, 
		int state, std::vector<std::string>& matches
	) = 0;
};