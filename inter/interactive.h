#include<iostream>
#include<string>
#include<vector>
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
using namespace std;

class Mediator {
	public:
		Mediator();
		std::string cline;
		bool called;
		
		void setinput(std::string input);
		std::string callback();
};

int interactive_Main();

#endif //INTERACTIVE_H