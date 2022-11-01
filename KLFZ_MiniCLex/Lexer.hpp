#pragma once
#include "Lex.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fmt/format.h>
#include <fmt/color.h>
#include <hv/TcpServer.h>

class Lexer
{
public:
	Lexer() {};
	~Lexer() {};
	virtual void start() = 0;
};

namespace MiniCLex {
	class IterLexer : public Lexer {
	public:
		void start() {
			while (true)
			{
				fmt::print(fmt::fg(fmt::color::light_green), "Waiting for input (ctrl+c to exit):\n");
				std::string line;
				std::getline(std::cin, line);
				lexer::start(line);
				auto& tokens = lexer::DFA::result.tokens;
				for (auto& token : tokens)
					std::cout << token.toString() << std::endl;
			}
		}
	};

	class NetworkLexer : public Lexer {
	private:
		unsigned short port = 23196;
	public:
		void start() {
			using namespace hv;
			TcpServer srv;
			int listenfd = srv.createsocket(port);
			if (listenfd < 0) {
				fmt::print(fmt::fg(fmt::color::red), "port {} is being used\n", port);
				exit(1);
			}
			fmt::print(fmt::fg(fmt::color::green), "server listen on port {}\n", port);
			srv.onConnection = [](const SocketChannelPtr& channel) {
				std::string clientaddr = channel->peeraddr();
				if(channel->isConnected())
					fmt::print(fmt::fg(fmt::color::light_green), "{} connected\n",clientaddr);
				else
					fmt::print(fmt::fg(fmt::color::light_yellow), "{} disconnected\n", clientaddr);
			};
			srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
				std::string recv((char*)buf->data());
				fmt::print("recieve: {}\n", recv);
				Buffer* send = new Buffer();
				lexer::start(recv);
				std::stringstream ss;
				auto& tokens = lexer::DFA::result.tokens;
				for (auto& token : tokens)
					ss << token.toString() << std::endl;
				send->copy((void*)ss.str().c_str(), (size_t)ss.str().size());
				channel->write(send);
				fmt::print("sended:\n {}", ss.str());
			};
			srv.onWriteComplete = [](const SocketChannelPtr& channel, Buffer* buf) {
				std::string send((char*)buf->data());
			};
			srv.start();
			while (getchar() != '\n');
			exit(0);
		}

		NetworkLexer* setPort(unsigned short port) {
			this->port = port;
			return this;
		}
	};

	class FileLexer : public Lexer {
	private:
		std::string inputPath = "input.txt";
		std::string outputPath = "output.txt";
	public:
		void start() {
			std::ifstream istream(inputPath);
			std::ofstream ostream(outputPath);
			if (!istream or !ostream) {
				fmt::print(fmt::fg(fmt::color::red), "can not touch input file or output file");
				exit(1);
			}
			std::string line;
			while (std::getline(istream,line))
			{
				lexer::start(line);
				auto& tokens = lexer::DFA::result.tokens;
				for (auto& token : tokens)
					ostream << token.toString() << std::endl;
			}
		}

		FileLexer* setInputPath(const std::string& iPath) {
			inputPath = iPath;
			return this;
		}

		FileLexer* setOutputPath(const std::string& oPath) {
			outputPath = oPath;
			return this;
		}
	};
}

Lexer* LexerFactory(const std::string& mod, int port = 23196) {
	if(mod == "network")
	{
		MiniCLex::NetworkLexer *lexer = new MiniCLex::NetworkLexer();
		lexer->setPort(port);
		return lexer;
	}
	else
	{
		MiniCLex::IterLexer* lexer = new MiniCLex::IterLexer();
		return lexer;
	}
}

Lexer* LexerFactory(const std::string& mod, const std::string& iPath, const std::string& oPath) {
	MiniCLex::FileLexer* lexer = new MiniCLex::FileLexer();
	lexer->setInputPath(iPath)
		->setOutputPath(oPath);
	return lexer;
}