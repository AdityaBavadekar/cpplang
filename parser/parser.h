#ifndef PARSER_H
#define PARSER_H
#include "../tokenizer/tokenizer.h"
#include "../logger/logger.h"
#include "../ast/ast.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Parser {

	private:
		std::vector<Token> tokens;
		std::vector<Expression>* returnExpressions;
		Logger logger;
		int index;
	public:
		Parser(std::vector<Token> _tokens,std::vector<Expression>* _returnExprs);
		void parse();
	
	private:
		void _parse();
		void handleKeyword(std::vector<Expression>* returnExprs);
		void handleIdentifier();
		bool hasNextToken();
		void skipSpace();
		bool cnext();
		Token gnext();
		Token ignext();
		bool expect(int type);
		void addExpression(Expression exp, std::vector<Expression>* returnExprs);
		Expression parseExpr(int id=0);
		StringExprPoint parseStringExpr(int id=0);
		BoolExprPoint parseBoolExpr(int id=0);
		NumberExprPoint parseIntExpr(int id=0);
		num_operation get_op(int type);
};

#endif //PARSER_H