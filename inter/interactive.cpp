#include "interactive.h"
#include<iostream>
#include<string>
#include<vector>
#include "..\tokenizer\tokenizer.h"
#include "..\parser\parser.h"
using namespace std;

const std::string INPUT_HINT = " >> ";
const std::string STREAM_NAME = "<stdin>";

#define SHOW_INPUT_HINT() std::cout << INPUT_HINT;

Mediator::Mediator():cline(""){}

void Mediator::setinput(std::string input){
	cline = input;
	called = false;
}

std::string Mediator::callback(){
	if(called) return "\0";
	called = true;
	return cline;
}

int interactive_Main(){
	Mediator md;
	CTokenizer tokenizer(STREAM_NAME, &md);
	
	std::cout << "-------- INTERACTIVE MODE --------" << std::endl;
	std::cout << "Type \"exit()\" or \"quit()\" to exit" << std::endl;
	SHOW_INPUT_HINT();
	
	std::string input;
	std::getline(std::cin, input);
	
	while(input != "exit()" && input != "quit()"){
		if(input == "exit"){
			std::cout << "Use exit() or quit() to exit" << std::endl;
		}else {
			md.setinput(input);
			try{
				tokenizer.tokenize();
			}catch(...){
				std::cerr << "Error Occurred!\n" << "Unknown Exception." << std::endl;
			}
			std::cout << tokenizer.string_list(false) << std::endl;
		}
		SHOW_INPUT_HINT();
		std::getline(std::cin, input);
	}
	
	
	
}

