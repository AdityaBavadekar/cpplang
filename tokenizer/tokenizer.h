#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "../constants/constants.h"
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
		s << " TOKEN [" << getTypeStringforType(type) << "]:[" << data << "]";
		return s.str();
	}
	
};


class CTokenizer {
	private:
		std::string file_path;
		int line_counter;
		int column_counter;
		std::string cline; // Current Line
		std::vector<Token> tokens;
		std::ifstream opened_file;
		int columnlimit;
	public:
	
		CTokenizer(std::string _file_path);
		// CTokenizer(std::string _file_path): file_path(_file_path), line_counter(0), column_counter(0), cline(""){};
		void tokenize();
		std::string string_list();
		
	private:
		void _tokenize();
		bool load_next_line();
		void parseInteger();
		void tryParseIdentifier();
		void parseStringLiteral();
		void parseMultilineComment();
		void parseComment();
		void addToken(int type, std::string data);
		void push_and_clear(std::string& collection);
		Token create_token(std::string data);

};

void tokenizer_Main(std::string file_path);

#endif  // TOKENIZER_H
