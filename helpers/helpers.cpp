#include "helpers.h"
#include<iostream>
#include<string.h>
using namespace std;

char int_to_string(int i){
	switch(i){
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '-';
	}
}

void sysexit(){
	system("PAUSE");
	exit(-1);
}

std::string charToString(char c){
	return std::string(""+c);
}

bool isInteger(std::string s){
	if (s == "" || !isdigit(s[0])) return false;
	for(int i = 0; i<s.length(); i++){
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