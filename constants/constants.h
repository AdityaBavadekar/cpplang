#ifndef CONSTANTS_H
#define CONSTANTS_H
#include<iostream>
#include <string.h>
#include <vector>

std::string getTypeStringforType(int type);

const char SYMBOLS[] = {'!','@','#','%','^','&','*','(',')','[',']','<','>','{','}','~','"',':','\'',';','?','.',',','|','\\','`','/'};

const std::string KEYWORDS[] = {
	"return",
	"if",
	"else",
	"while",
	"when",
	"do",
	"type",
	"int",
	"string",
	"long",
	"double",
	"for",
	"break",
	"continue",
	"try",
	"catch",
	"float",
	"uses",
	"throw",
	"fun",
	"abstract",
	"in",
	"is",
	"clear",
	"class",
	"enum",
	"interface",
	"private",
	"public",
	"protected",
	"bool",
	"as",
	"this",
	"null",
	"true",
	"false"
};

const std::string SUPPORTED_DATATYPES[] = {
	"int",
	"bool",
	"string"
};

enum TokenType {
	IDENTIFIER = 0,
	INTEGER = 1,
	ASSIGNMENT = 2,
	PRINT = 3,
	STRING = 4,
	END_OF_FILE = 5,
	BOOL = 6,
	NEWLINE = 7,
	INDENT = 8,
	COMMA = 9,
	COLON = 10,
	SEMI = 11,
	PLUS = 12,
	MINUS = 13,
	RSLASH = 14,
	LSLASH = 15,
	GREATER = 16,
	LESS = 17,
	EQUAL = 18,
	DOT = 19,
	EXCLAMATION = 20,
	AT = 21,
	HASHTAG = 22,
	DOLLAR = 23,
	PERCENT = 24,
	UP = 25,
	AND = 26,
	STAR = 27,
	UNDERSCORE = 28,
	TILDE = 29,
	BACKTIK = 30,
	SINGLEQUOTE = 31,
	DOUBLEQUOTE = 32,
	CIRCLEBRACKETSTART = 33,
	CIRCLEBRACKETEND = 34,
	SQUAREBRACKETSTART = 35,
	SQUAREBRACKETEND = 36,
	CURLYBRACKETSTART = 37,
	CURLYBRACKETEND = 38,
	PIPE = 39,
	USES = 40,
	SPACE = 41,
	ELIPSIS = 42,
	TYPE_IGNORE = 43,
	KEYWORD = 44,
	UNK = 45,
	END = 46,
	OTHER = 47,
};

#endif //CONSTANTS_H