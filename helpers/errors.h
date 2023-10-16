#ifndef ERRORS_H
#define ERRORS_H
#include<iostream>
#include<string>
#include<vector>
#include "helpers.h"
#include "..\ast\ast.h"
using namespace std;

/* 
	This file contains all All Exceptions that can be thrown 
*/

#define ERR_SYNTAX 101
#define ERR_RUNTIME 102
#define ERR_ILLEGAL_ARGUMENT 103
#define fire_illegal_argument_error(msg, tcol, tline, tfile) fire_error(ERR_ILLEGAL_ARGUMENT, msg, tcol, tline, tfile)
#define fire_runtime_error(msg, tcol, tline, tfile) fire_error(ERR_RUNTIME, msg, tcol, tline, tfile)
#define fire_syntax_error(msg, tcol, tline, tfile) fire_error(ERR_SYNTAX, msg, tcol, tline, tfile)

#define fire_error(type, tmsg, tcol, tline, tfile) ErrorTree etree(__LINE__, __FILE__);\
	etree.targetLineNo = tline;\
	etree.targetColNo = tcol;\
	etree.targetFile = tfile;\
	etree.msg = tmsg;\
	ErrorTrace tr(tfile, etree);\
	Error er(type, tmsg);\
	er.fire(tr);

/* BASE CLASS */
struct ErrorTree : Null {
	std::string msg;
	/*
	srcLine and srcFile for the file the creates this error tree. 
	Use __LINE__ and __FILE__
	For eg:
		```
		Error error(__LINE__, __FILE__);
		int srcLineNo = __LINE__;
		```
	*/
	int srcLineNo;
	std::string srcFile;
	/* line and file are for the file being parsed and it location of error. */
	int targetLineNo;
	int targetColNo;
	std::string targetFile;
	std::vector<ErrorTree> children;
	ErrorTree() : Null(true){};
	ErrorTree(int _srcLineNo, std::string _srcFile) : Null(false),
	srcLineNo(_srcLineNo),srcFile(_srcFile){};

};

struct ErrorTrace{
	std::string file_path;
	ErrorTree tree;
	bool valid;
	ErrorTrace():valid(false){};
	ErrorTrace(std::string _file_path, ErrorTree _tree):valid(true),file_path(_file_path),tree(_tree){};
};

class Error : public std::exception {
	public:
		std::string message;
		Error(int type, const std::string message_);
		const char* what() const noexcept override {
			return message.c_str();
		}
		void fire(ErrorTrace trace, std::string extra_string = "");
	private:
		void print(ErrorTree trace);
};

/* ERRORS */
/* Parsing */
//const Error NonTerminatedString;

const std::string Msg_StringNotTerminated = "String Liternal not terminated";
const int Code_StringNotTerminated = 100;
const Error NonTerminatedString(Code_StringNotTerminated, Msg_StringNotTerminated);

const std::string Msg_CommentNotTerminated = "Multiline comment not terminated";
const int Code_CommentNotTerminated = 101;

#endif