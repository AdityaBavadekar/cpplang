#include "constants.h"
#include<iostream>
#include<string>
using namespace std;

std::string getTypeStringforType(int type){
	switch (type)
	{
	case IDENTIFIER:
		return "identifier";
	case INTEGER:
		return "integer";
	case BOOL:
		return "boolean";
	case ASSIGNMENT:
		return "assignment";
	case PRINT:
		return "print";
	case STRING:
		return "string";
	case END_OF_FILE:
		return "endoffile";
	case NEWLINE:
		return "NEWLINE";
	case INDENT:
		return "INDENT";
	case COMMA:
		return "COMMA";
	case COLON:
		return "COLON";
	case SEMI:
		return "SEMI";
	case PLUS:
		return "PLUS";
	case MINUS:
		return "MINUS";
	case RSLASH:
		return "RSLASH";
	case LSLASH:
		return "LSLASH";
	case GREATER:
		return "GREATER";
	case LESS:
		return "LESS";
	case EQUAL:
		return "EQUAL";
	case DOT:
		return "DOT";
	case EXCLAMATION:
		return "EXCLAMATION";
	case AT:
		return "AT";
	case HASHTAG:
		return "HASHTAG";
	case DOLLAR:
		return "DOLLAR";
	case PERCENT:
		return "PERCENT";
	case UP:
		return "UP";
	case AND:
		return "AND";
	case STAR:
		return "STAR";
	case UNDERSCORE:
		return "UNDERSCORE";
	case TILDE:
		return "TILDE";
	case BACKTIK:
		return "BACKTIK";
	case SINGLEQUOTE:
		return "SINGLEQUOTE";
	case DOUBLEQUOTE:
		return "DOUBLEQUOTE";
	case CIRCLEBRACKETSTART:
		return "CIRCLEBRACKETSTART";
	case CIRCLEBRACKETEND:
		return "CIRCLEBRACKETEND";
	case SQUAREBRACKETSTART:
		return "SQUAREBRACKETSTART";
	case SQUAREBRACKETEND:
		return "SQUAREBRACKETEND";
	case CURLYBRACKETSTART:
		return "CURLYBRACKETSTART";
	case CURLYBRACKETEND:
		return "CURLYBRACKETEND";
	case ELIPSIS:
		return "ELIPSIS";
	case TYPE_IGNORE:
		return "type_ignore";
	case END:
		return "end";
	case OTHER:
		return "other";
	default:
		return "UNK";
		break;
	}
}