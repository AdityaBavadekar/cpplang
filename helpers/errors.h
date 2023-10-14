#ifndef ERRORS_H
#define ERRORS_H
#include<iostream>
#include<string>
#include "helpers.h"
using namespace std;

/* 
	This file contains all All Exceptions that can be thrown 
*/

/* BASE CLASS */
class Error : public std::exception {
	public:
		std::string message;
		Error(int type, const std::string message_);
		const char* what() const noexcept override {
			return message.c_str();
		}
		void fire(std::string file_path, std::string line, int lineno, int columnno, std::string extra_string = "");
};

/* ERRORS */
/* Parsing */
//const Error NonTerminatedString;

const std::string Msg_NonTerminatedString = "String Liternal not terminated";
const int Code_NonTerminatedString = 100;
const Error NonTerminatedString(Code_NonTerminatedString, Msg_NonTerminatedString);

const std::string Msg_CommentNotTerminated = "Multiline comment not terminated";
const int Code_CommentNotTerminated = 101;

#endif