#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "..\constants\constants.h"
#include "..\inter\interactive.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include<iostream>

struct Token{
	std::string data;
	int type;
	int lineno;
	int columnno;
	std::string file_path;

	std::string to_string(){
		std::stringstream s;
		s << "[(" << getTypeStringforType(type) << ") " << data << "]";
		return s.str();
	}
	
};


class CTokenizer {
	private:
		std::string file_path;
		Mediator* md;
		bool interactive;
		int line_counter;
		int column_counter;
		std::string cline; // Current Line
		std::vector<Token> tokens;
		std::ifstream opened_file;
		int columnlimit;
	public:
		CTokenizer(std::string name, Mediator* md);
		CTokenizer(std::string _file_path);
		void tokenize();
		std::string string_list();
		std::vector<Token> get_tokens();
		~CTokenizer();
	private:
		bool load_next_line();
		void _tokenize();
		void parseInteger();
		void tryParseIdentifier();
		void parseStringLiteral();
		void parseMultilineComment();
		void parseComment();
		void addToken(int type, std::string data);
		void push_and_clear(std::string& collection);
		Token create_token(std::string data);

};

std::vector<Token> tokenizer_Main(std::string file_path);

#endif  // TOKENIZER_H
