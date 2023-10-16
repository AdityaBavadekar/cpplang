#ifndef PARSER_H
#define PARSER_H
#include "../tokenizer/tokenizer.h"
#include "../ast/ast.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Parser {

	private:
		std::vector<Token> tokens;
		int index;
	public:
		Parser(std::vector<Token> _tokens);
		void parse();
	
	private:
		void _parse();
		void handleKeyword();
		void handleIdentifier();
		bool hasNextToken();
		void skipSpace();
		bool cnext();
		Token gnext();
		Token ignext();
		bool expect(int type);
		Expression parseExpr(int id=0);
		StringExprPoint parseStringExpr(int id=0);
		BoolExprPoint parseBoolExpr(int id=0);
		NumberExprPoint parseIntExpr(int id=0);
		num_operation get_op(int type);
};

#endif //PARSER_H