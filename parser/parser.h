#ifndef PARSER_H
#define PARSER_H
#include "../tokenizer/tokenizer.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Parser {

	private:
		std::vector<Token> tokens;
		int index;
	public:
	
		Parser(std::vector<Token>& _tokens) : tokens(_tokens) {
			
		}
		void parse(){
			_parse();
		}
	
	private:
		void _parse(){
			while(hasNextToken()){
				
			}
		}
	
		bool hasNextToken(){
			return index < tokens.size() - 1;
		}
};

#endif //PARSER_H