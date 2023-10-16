#include "helpers.h"
#include "../constants/constants.h"
#include "../ast/ast.h"
#include "errors.h"
#include<iostream>
#include<sstream>
#include<string.h>
using namespace std;

int string_to_int(std::string s){
	Number i;
	try{
		for(int index = 0;index<s.length(); index++){
			if(s[index] == '0' && i.isnull){
				continue;
			}
			switch(s[index]){
				case '0': 
					i = i*Number(10) + 0;
					break;
				case '1': 
					i = i*Number(10) + 1;
					break;
				case '2': 
					i = i*Number(10) + 2;
					break;
				case '3': 
					i = i*Number(10) + 3;
					break;
				case '4': 
					i = i*Number(10) + 4;
					break;
				case '5': 
					i = i*Number(10) + 5;
					break;
				case '6': 
					i = i*Number(10) + 6;
					break;
				case '7': 
					i = i*Number(10) + 7;
					break;
				case '8': 
					i = i*Number(10) + 8;
					break;
				case '9': 
					i = i*Number(10) + 9;
					break;
				default:
					throw Error(-1,"");
			}
		}
	}catch(...){
		return -1;
	}
	if(i.isnull) return -1;
	return i.n;
}

BoolExprPoint string_to_bool(std::string s){
	if(s == "true") return BoolExprPoint(true);
	if(s == "false") return BoolExprPoint(false);
	return BoolExprPoint();
}

std::string int_to_string(int i){
	std::string number = "";
	while(i > 0){
		int digit = i % 10;
		i /= 10;
		switch(i){
			case 0: 
				number += '0';
				break;
			case 1: 
				number += '1';
				break;
			case 2: 
				number += '2';
				break;
			case 3: 
				number += '3';
				break;
			case 4: 
				number += '4';
				break;
			case 5: 
				number += '5';
				break;
			case 6: 
				number += '6';
				break;
			case 7: 
				number += '7';
				break;
			case 8: 
				number += '8';
				break;
			case 9: 
				number += '9';
				break;
			default:
				//TODO("Negative numbers")
				std::stringstream ss;
				ss << "Not a number (" << i << ")";
				throw Error(-1, ss.str());
		}
	}
	return number;
}

void sysexit(){
	exit(-1);
}

std::string charToString(char c){
	return ""+c;
}

bool isInteger(std::string s){
	for(int i = 0; i<s.length(); i++){
		std::cout << "isInteger[" << s[i] << "]\n";
		if(isdigit(s[i])) continue;
		else return false;
	}
	return true;
}

void replace(std::string &str, const std::string &search, const std::string &replace) {
    size_t pos = 0;
    while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

bool contains(const std::string& s, const std::string& x) {
    return s.find(x) != std::string::npos;
}

bool isIdentifierChar(char c){
	return (isalpha(c) || c == '_');
}

int isKeyword(std::string s){
	for(const auto& pair : KEYWORD_TO_TYPE){
		if(s == pair.first){
			return pair.second;
		}
	}
	return -1;
}