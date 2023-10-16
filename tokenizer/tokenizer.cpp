#include "tokenizer.h"
#include "..\helpers\helpers.h"
#include "..\helpers\errors.h"
#include "..\constants\constants.h"
#include "..\inter\interactive.h"
#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

CTokenizer::CTokenizer(std::string name, Mediator* md): file_path(name), line_counter(0), column_counter(0), columnlimit(0), cline(""), interactive(true), md(md)
{}

CTokenizer::CTokenizer(std::string _file_path): file_path(_file_path), line_counter(0), column_counter(0), columnlimit(0), cline(""), interactive(false)
{
	opened_file.open(file_path.c_str());
	if(!opened_file.is_open()){
		std::cerr << "Error : Could not open the file \nFile : [" << file_path << "]" << std::endl;
		sysexit();
	}
}

void CTokenizer::tokenize(){
	_tokenize();
}

std::string CTokenizer::string_list(){
	std::stringstream s;
	s << "Tokens found " << tokens.size() << std::endl;
	for(int i = 0; i< tokens.size(); i++){
		s << tokens[i].to_string() + " ";//"\n";
	}
	return s.str();
}

Token CTokenizer::create_token(std::string data){
	Token tk;
	tk.data = data;
	tk.lineno = line_counter;
	tk.columnno = column_counter;
	tk.file_path = file_path;
	tk.type = -1;
	return tk;
}

void CTokenizer::push_and_clear(std::string& collection) {
	if (collection == "") return;

	Token tk = create_token(collection);
	tokens.push_back(tk);
	collection = "";
};

void CTokenizer::addToken(int type, std::string data){
	//Do not add empty tokens
	if(data == "") return;
	
	Token tk = create_token(data);
	tk.type = type;
	tokens.push_back(tk);
}

void CTokenizer::parseStringLiteral(){
	int startlineno = line_counter;
	int startcolumnno = column_counter;
	char c1 = cline[column_counter - 1];
	if (c1 != '\'' && c1!= '"') return;
	
	if (column_counter == columnlimit) throw NonTerminatedString;

	column_counter++;
	char c2 = cline[column_counter - 1];
	std::string s = "";
	
	while(c2 != c1){
		s += c2;
		if(column_counter == columnlimit) break;
		
		column_counter++;
		c2 = cline[column_counter - 1];
	}
	
	if(c2 != c1 && column_counter == columnlimit){
		//ERROR : String Literal Not Terminated.
		fire_syntax_error(Msg_StringNotTerminated, startcolumnno, startlineno, file_path);
	}
	if(s != "") addToken(STRING, s);

	// Change current char from the " or ' to next one.
	if (column_counter != columnlimit) column_counter++; 
}

void CTokenizer::parseMultilineComment(){
	int startlineno = line_counter;
	std::string startline = cline;
	int startcolumnno = column_counter;
	char c = cline[column_counter - 1];
	if(c != '|' || column_counter + 1 > columnlimit) return;
	
	column_counter++;
	char c2 = cline[column_counter - 1];
	
	column_counter++;
	char c3 = cline[column_counter - 1];
	
	if(c2 != '|' || c3 != '|') {
		column_counter -= 2;
		return;
	}
	
	bool terminated = false;
	while(load_next_line()){
		if(contains(cline, "|||")){
			int index = cline.find("|");
			if(index != columnlimit-2 && cline[index+1] == '|' && cline[index+2] == '|') {
				column_counter = index+2+1;
				terminated = true;
				break;
			}
		}
	}
	
	if(!terminated){
		//ERROR : Multiline Comment is not terminated
		fire_syntax_error(Msg_CommentNotTerminated, startcolumnno, startlineno, file_path);
	}
}
	
void CTokenizer::parseComment(){
	char c = cline[column_counter - 1];
	if(c != '/' || column_counter == columnlimit) return;
	column_counter++;
	c = cline[column_counter - 1];
	if(c != '/') return;
	// Skip the current line as it is a single line comment.
	load_next_line();
}


void CTokenizer::parseInteger(){
	char c = cline[column_counter - 1];
	std::string stringInt = "";
	if (!isdigit(c)) return;
	while(isdigit(c)){
		stringInt += c;
		if(column_counter == columnlimit){
			break;
		}
		column_counter++;
		c = cline[column_counter - 1];
	}
	
	if(stringInt != ""){
		addToken(INTEGER, stringInt);
	}
}

void CTokenizer::tryParseIdentifier(){
	char c = cline[column_counter - 1];
	std::string identifier = "";
	if (!isIdentifierChar(c)) return;
	
	while(isIdentifierChar(c)){
		identifier += c;
		if(column_counter == columnlimit) break;
		column_counter++;
		c = cline[column_counter - 1];
	}
	
	if (identifier != "") {
		int stat = isKeyword(identifier);
		if(stat != -1){
			addToken(stat, identifier);
		}else addToken(IDENTIFIER,identifier);
	}
}

void CTokenizer::_tokenize(){
	while(load_next_line()){
		while(column_counter != columnlimit){
			column_counter++;
			
			// Column counter always stores column number which 
			// is current index from start + 1
			char c = cline[column_counter - 1];
			//Try to parse Integers if valid
			if(isdigit(c)) parseInteger();
			
			//Try to Parse words
			if(isIdentifierChar(c)) tryParseIdentifier();

			c = cline[column_counter - 1];
			switch (c) {
				case '\t':
					addToken(INDENT, "\t");
					break;
				case ' ':
				case '\r':
				case '\n':
					break;
				case '"':
				case '\'':
					parseStringLiteral();
					break;
				case '(':
					addToken(CIRCLEBRACKETSTART, "(");
					break;
				case ')':
					addToken(CIRCLEBRACKETEND, ")");
					break;
				case '{':
					addToken(CURLYBRACKETSTART, "{");
					break;
				case '}':
					addToken(CURLYBRACKETEND, "}");
					break;
				case '[':
					addToken(SQUAREBRACKETSTART, "[");
					break;
				case ']':
					addToken(SQUAREBRACKETEND, "]");
					break;
				case ';':
					addToken(SEMI, ";");
					break;
				case ':':
					addToken(COLON, ":");
					break;
				case '>':
					addToken(LGREATER, ">");
					break;
				case '<':
					addToken(LLESS, "<");
					break;
				case '+':
					addToken(PLUS, "+");
					break;
				case '-':
					addToken(MINUS, "-");
					break;
				case '.':
					addToken(DOT, ".");
					break;
				case ',':
					addToken(COMMA, ",");
					break;
				case '*':
					addToken(STAR, "*");
					break;
				case '_':
					addToken(UNDERSCORE, "_");
					break;
				case '^':
					addToken(UP, "^");
					break;
				case '#':
					addToken(HASHTAG, "#");
					break;
				case '&':
					addToken(AND, "&");
					break;
				case '@':
					addToken(AT, "*");
					break;
				case '%':
					addToken(PERCENT, "*");
					break;
				case '!':
					addToken(EXCLAMATION, "*");
					break;
				case '=':
					addToken(EQUAL, "=");
					break;
				case '|':
					if(column_counter + 1 <= columnlimit && cline[column_counter] == '|' && cline[column_counter + 1] == '|'){
						parseMultilineComment();
					}else addToken(PIPE, "|");
					break;
				case '\\':
					addToken(LSLASH, "\\");
					break;
				case '/':
					if(column_counter != columnlimit && cline[column_counter] == '/'){
						parseComment();
					}else addToken(RSLASH, "/");
					break;
				default:
					break;
			}
		}
			
		addToken(LINE_END, "...");
    }

	addToken(END_OF_FILE,"...");
	
}

bool CTokenizer::load_next_line(){
	
	if(interactive){
		std::string res = md->callback();
		if(res == "\0") {
			return false;
		}
		cline = res;
		//Reset Previous Parameters
		line_counter = 0;
		tokens.clear();
	}
	else if(!std::getline(opened_file, cline)){
		//EOF
		return false;
	}
	line_counter++;
	// Reinitialize column counter to zero.
	column_counter = 0;
	// Store last column index
	columnlimit = cline.length();
	return true;
}

std::vector<Token> CTokenizer::get_tokens(){
	return tokens;
}

CTokenizer::~CTokenizer(){
	opened_file.close();
}

std::vector<Token> tokenizer_Main(std::string file_path){
	std::string FILE = file_path;
	CTokenizer ctk(FILE);
	ctk.tokenize();
	std::cout << ctk.string_list();
	std::ofstream f("..\\compilation_tokens.txt");
	f << ctk.string_list();
	f.close();
	return ctk.get_tokens();
}
