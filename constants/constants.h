#ifndef CONSTANTS_H
#define CONSTANTS_H
#include<iostream>
#include <string.h>
#include <vector>
#include <map>
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
	"delete",
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
	LGREATER = 16, // > (GREATER w.r.t Left side)
	LLESS = 17, // < (LESS w.r.t Left side)
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
	/* start keywords */
	K_IF = 45,
	K_ELSE = 46,
	K_WHILE = 47,
	K_WHEN = 48,
	K_FOR = 49,
	K_TRY = 50,
	K_RETURN = 51,
	K_INT = 52,
	K_STRING = 53,
	K_BOOL = 54,
	K_BREAK = 55,
	K_CONTINUE = 56,
	K_USES = 57,
	K_FUN = 58,
	K_CLASS = 59,
	K_ENUM = 60,
	K_PUBLIC = 61,
	K_PRIVATE = 62,
	K_PROTECTED = 63,
	K_NULL = 64,
	K_TRUE = 65,
	K_FALSE = 66,
	K_AS = 67,
	K_THIS = 68,
	K_CLEAR = 69,
	K_IN = 70,
	K_DELETE = 71,
	// 70...80 reserved for new keywords
	/* end keywords */
	LINE_END = 81,
	UNK = 80
};

const int TOKEN_KEYWORD_START = 45;
const int TOKEN_KEYWORD_END = 80;

const std::map<std::string, int> KEYWORD_TO_TYPE = {
	{ "if", K_IF },
	{ "else", K_ELSE },
	{ "while", K_WHILE },
	{ "when", K_WHEN },
	{ "for", K_FOR },
	{ "try", K_TRY },
	{ "return", K_RETURN },
	{ "int", K_INT },
	{ "string", K_STRING },
	{ "bool", K_BOOL },
	{ "break", K_BREAK },
	{ "continue", K_CONTINUE },
	{ "uses", K_USES },
	{ "fun", K_FUN },
	{ "class", K_CLASS },
	{ "enum", K_ENUM },
	{ "public", K_PUBLIC },
	{ "private", K_PRIVATE },
	{ "protected", K_PROTECTED },
	{ "null", K_NULL },
	{ "true", K_TRUE },
	{ "false", K_FALSE },
	{ "as", K_AS },
	{ "this", K_THIS },
	{ "clear", K_CLEAR },
	{ "in", K_IN },
	{ "delete", K_DELETE },
};

#endif //CONSTANTS_H