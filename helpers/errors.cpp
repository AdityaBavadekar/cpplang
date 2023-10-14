#include "errors.h"
#include<iostream>
using namespace std;


/* ERRORS */

/* Parsing */



/* BASE CLASS */
Error::Error(int type, const std::string message_):message(message_){}

void Error::fire(std::string file_path, std::string line, int lineno, int columnno, std::string extra_string){
	std::cerr << "Error ! " << message << std::endl;
	std::cerr << "in file " << file_path << "\t Line " << lineno << ", Column " << columnno << std::endl;
	std::cerr << line << std::endl;
	if(columnno > 2){
		std::string s = "";
		for (int i = 0; i < columnno-2; i++){
			s += " ";
		}
		s += "^";
		std::cerr << s << std::endl;
	}
	cerr << extra_string << std::endl;
	sysexit();
}

