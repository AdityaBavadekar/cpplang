#include "errors.h"
#include<iostream>
using namespace std;


/* ERRORS */

/* Parsing */


/* BASE CLASS */
Error::Error(int type, const std::string message_):message(message_){}

void Error::print(ErrorTree tree){
	std::cerr << " ### " << tree.msg          << std::endl; 
	std::cerr << "Line " << tree.srcLineNo    << ", from File : " << tree.srcFile     << std::endl;
	std::cerr << "Line " << tree.targetLineNo << "\tColumn " << tree.targetColNo << ", from File : " << tree.targetFile << std::endl;
	for(int i = 0; i<tree.children.size(); i++){
		print(tree.children[i]);
	}
}

void Error::fire(ErrorTrace trace, std::string extra_string){
	std::cerr << "Error !" << std::endl;
	/* if(columnno > 2){
		std::string s = "";
		for (int i = 0; i < columnno-2; i++){
			s += " ";
		}
		s += "^";
		std::cerr << s << std::endl;
	} */
	print(trace.tree);
	std::cerr << extra_string << std::endl;
	sysexit();
}

