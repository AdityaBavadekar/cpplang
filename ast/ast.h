#ifndef AST_H
#define AST_H
#include<iostream>
#include<vector>
#include<string>
#include "..\tokenizer\tokenizer.h"
using namespace std;

struct AST {
	std::string name;
	std::vector<AST> children;
	std::vector<Token> tokens;
	
	bool hasChildren(){
		return children.size() > 0;
	}
	bool hasTokens(){
		return tokens.size() > 0;
	}
};

#endif //AST_H