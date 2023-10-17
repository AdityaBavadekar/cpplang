#ifndef LOGGER_H
#define LOGGER_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Logger{
	
	enum log_level {ERROR=0, WARN=1, DEBUG=3};
	std::string name;
	public:
		Logger(std::string _name):name(_name){};
		
		template<typename T>
		Logger operator<<(const T data){
			std::cout << "[L][" << name << "]:" << data << std::endl;
			return this;
		}
	
};

#endif //LOGGER_H