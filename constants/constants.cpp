#include "constants.h"
#include<iostream>
#include<string>
#include "..\helpers\helpers.h"
using namespace std;

std::string getTypeStringforType(int type){
	switch (type)
	{
	/*  */
	case IDENTIFIER :
		return "IDENTIFIER";
		break;
	case INTEGER :
		return "INTEGER";
		break;
	case ASSIGNMENT :
		return "ASSIGNMENT";
		break;
	case PRINT :
		return "PRINT";
		break;
	case STRING :
		return "STRING";
		break;
	case END_OF_FILE :
		return "END_OF_FILE";
		break;
	case BOOL :
		return "BOOL";
		break;
	case NEWLINE :
		return "NEWLINE";
		break;
	case INDENT :
		return "INDENT";
		break;
	case COMMA :
		return "COMMA";
		break;
	case COLON :
		return "COLON";
		break;
	case SEMI :
		return "SEMI";
		break;
	case PLUS :
		return "PLUS";
		break;
	case MINUS :
		return "MINUS";
		break;
	case RSLASH :
		return "RSLASH";
		break;
	case LSLASH :
		return "LSLASH";
		break;
	case LGREATER :
		return "LGREATER";
		break;
	case LLESS :
		return "LLESS";
		break;
	case EQUAL :
		return "EQUAL";
		break;
	case DOT :
		return "DOT";
		break;
	case EXCLAMATION :
		return "EXCLAMATION";
		break;
	case AT :
		return "AT";
		break;
	case HASHTAG :
		return "HASHTAG";
		break;
	case DOLLAR :
		return "DOLLAR";
		break;
	case PERCENT :
		return "PERCENT";
		break;
	case UP :
		return "UP";
		break;
	case AND :
		return "AND";
		break;
	case STAR :
		return "STAR";
		break;
	case UNDERSCORE :
		return "UNDERSCORE";
		break;
	case TILDE :
		return "TILDE";
		break;
	case BACKTIK :
		return "BACKTIK";
		break;
	case SINGLEQUOTE :
		return "SINGLEQUOTE";
		break;
	case DOUBLEQUOTE :
		return "DOUBLEQUOTE";
		break;
	case CIRCLEBRACKETSTART :
		return "CIRCLEBRACKETSTART";
		break;
	case CIRCLEBRACKETEND :
		return "CIRCLEBRACKETEND";
		break;
	case SQUAREBRACKETSTART :
		return "SQUAREBRACKETSTART";
		break;
	case SQUAREBRACKETEND :
		return "SQUAREBRACKETEND";
		break;
	case CURLYBRACKETSTART :
		return "CURLYBRACKETSTART";
		break;
	case CURLYBRACKETEND :
		return "CURLYBRACKETEND";
		break;
	case PIPE :
		return "PIPE";
		break;
	case USES :
		return "USES";
		break;
	case SPACE :
		return "SPACE";
		break;
	case ELIPSIS :
		return "ELIPSIS";
		break;
	case TYPE_IGNORE :
		return "TYPE_IGNORE";
		break;
	case KEYWORD :
		return "KEYWORD";
		break;
	case K_IF :
		return "IF";
		break;
	case K_ELSE :
		return "ELSE";
		break;
	case K_WHILE :
		return "WHILE";
		break;
	case K_WHEN :
		return "WHEN";
		break;
	case K_FOR :
		return "FOR";
		break;
	case K_TRY :
		return "TRY";
		break;
	case K_RETURN :
		return "RETURN";
		break;
	case K_INT :
		return "INT";
		break;
	case K_STRING :
		return "STRING";
		break;
	case K_BOOL :
		return "BOOL";
		break;
	case K_BREAK :
		return "BREAK";
		break;
	case K_CONTINUE :
		return "CONTINUE";
		break;
	case K_USES :
		return "USES";
		break;
	case K_FUN :
		return "FUN";
		break;
	case K_CLASS :
		return "CLASS";
		break;
	case K_ENUM :
		return "ENUM";
		break;
	case K_PUBLIC :
		return "PUBLIC";
		break;
	case K_PRIVATE :
		return "PRIVATE";
		break;
	case K_PROTECTED :
		return "PROTECTED";
		break;
	case K_NULL :
		return "NULL";
		break;
	case K_TRUE :
		return "TRUE";
		break;
	case K_FALSE :
		return "FALSE";
		break;
	case K_AS :
		return "AS";
		break;
	case K_THIS :
		return "THIS";
		break;
	case K_CLEAR :
		return "CLEAR";
		break;
	case K_IN :
		return "IN";
		break;
	case LINE_END :
		return "LINE_END";
		break;
	default:
		return "UNK(="+int_to_string(type)+")";
		break;
	}
}