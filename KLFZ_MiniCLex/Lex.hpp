#pragma once
#include "MiniC.hpp"
#include "FlowModel.hpp"
#include <regex>
#include <sstream>

// Input stream reader
namespace MiniCLex
{
	namespace lexer {
		using std::string;
		mini_c::MiniCFlowModel flowModel;
		void resetDefault();
		void start(const string& stream);

		namespace DFA {
			using std::string;
			using std::vector;
			void toDefault();
			void pushToTokens(const token& token);
			void pushToMatches(const string& match);
			void filterTokens();
			void produceToken();
			void flowToNextState(const string& ch, int nextState);
			void flowToResetState();
			int state = 0; // 0 is the default state id of RESET
			struct Result
			{
				vector<string> matches;
				vector<token> tokens;
			} result;
		}
		namespace ISR {
			void incSeq();
			void toDefault();
			void before(const string& stream);
			void after();
			string nextChar();
			bool isLastChar();
			void read();
			struct Props {
				string stream;
				int length = 0;
				int seq = 0;
			} props;
		}

		// Input stream reader
		namespace ISR {

			void incSeq() { props.seq++; }

			void toDefault()
			{
				props.stream = "";
				props.length = 0;
				props.seq = 0;
			}

			void before(const string& stream)
			{
				props.stream = string(stream);
				props.stream =
					std::regex_replace(props.stream, std::regex("\n+"), "\n");
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
				props.length = props.stream.length();
			}

			void after()
			{
				DFA::filterTokens();
			}

			string nextChar()
			{
				int seq = props.seq;
				if (seq <= props.length - 1)
					return { props.stream[seq] };
				return "";
			}

			bool isLastChar()
			{
				return props.seq == props.length - 1;
			}

			void read()
			{
				string ch;
				while ((ch = lexer::ISR::nextChar()) != "") {
					bool match = false;
					bool end = false;
					int state = DFA::state;
					int nextState = flowModel.getNextState(ch, state, DFA::result.matches);

					if (nextState != mini_c::DFA_STATE.at("RESET")) {
						match = true;
						if (ISR::isLastChar())
							end = true;
					}
					Path path = {
						state,ch,nextState,match,end
					};
					flowModel.pathGrow(path);
					if (match) {
						ISR::incSeq();
						DFA::flowToNextState(ch, nextState);
						if (end) {
							DFA::produceToken();
						}
					}
					else {
						DFA::produceToken();
						DFA::flowToResetState();
					}
				}
			}
		}

		// DFA Model
		namespace DFA {

			void toDefault()
			{
				state = 0;
				result.matches.clear();
				result.tokens.clear();
			}

			void pushToTokens(const token& token) {
				result.tokens.push_back(token);
				result.matches.clear();
			}

			void pushToMatches(const string& match) {
				result.matches.push_back(match);
			}

			void filterTokens() {
				vector<token> tokens;
				for (auto& token : result.tokens) {
					if (token.value != " "
						&& token.value != "\n"
						&& token.value != "\t"
						&& token.value != "\r") {
						tokens.push_back(token);
					}
				}
				result.tokens = tokens;
			}

			void produceToken() {
				if (!result.matches.empty()) {
					std::stringstream ss;
					for (auto& match : result.matches) {
						ss << match;
					}
					string value = ss.str();
					string type = mini_c::getTokenType(state, value);
					pushToTokens({ type,value });
				}
			}

			void flowToNextState(const string& ch, int nextState) {
				pushToMatches(ch);
				state = nextState;
			}

			void flowToResetState() {
				state = mini_c::DFA_STATE.at("RESET");
			}
		}

		void resetDefault() {
			DFA::toDefault();
			ISR::toDefault();
			flowModel.toDefault();
		}

		void start(const string& stream) {
			resetDefault();
			ISR::before(stream);
			ISR::read();
			ISR::after();
		}
	}
}