#ifndef HELPERS_H
#define HELPERS_H
#include<iostream>
#include "../ast/ast.h"
#include<string>
#include<sstream>
/* 
#define TO_STRING(value) \
	[](){\
		std::stringstream ss;\
		ss << value;\
		return ss.str();\
	}() 
*/

#define LOG(value) \
	[](){\
		std::cout << TO_STRING(value) << std::endl;\
	}()

int string_to_int(std::string s);
BoolExprPoint string_to_bool(std::string s);
std::string int_to_string(int i);
void sysexit();
std::string charToString(char c);
bool isInteger(std::string s);
void replace(std::string &str, const std::string &search, const std::string &replace);
bool contains(const std::string& s, const std::string& x);
bool isIdentifierChar(char c);
int isKeyword(std::string s);

# endif //HELPERS_H