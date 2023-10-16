#include "parser.h"
#include "..\helpers\helpers.h"
#include "..\helpers\errors.h"
#include "..\constants\constants.h"
#include "..\ast\ast.h"
#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;


Parser::Parser(std::vector<Token> _tokens) : tokens(_tokens), index(0){	
}

void Parser::parse(){
	_parse();
}

void Parser::_parse(){
	while(hasNextToken()){
		Token tk = tokens[index];
		if(tk.type == END_OF_FILE) break;
		
		if(tk.type >= 45 && tk.type <= 70){
			//Keyword
			handleKeyword();
		}
		if(tk.type == IDENTIFIER){
			handleIdentifier();
		}
		index++;
	}
	std::cout << "Normal program executed." << std::endl;
}

void Parser::skipSpace(){
	if (cnext() && gnext().type == SPACE) index++;
}

/* 
	Returns has next token or not.
 */
bool Parser::cnext(){
	int max = tokens.size() - 1;
	return (index < max);
}

/* 
	Returns next token or throws Error.
 */
Token Parser::gnext(){
	if(cnext()){
		return tokens[index+1];
	}else{
		Token current = tokens[index];
		fire_syntax_error("Syntax Error next element required after '" + current.data + "'", current.columnno, current.lineno, current.file_path);
	}
}

/* 
	Returns next token and increments index or throws Error.
 */
Token Parser::ignext(){
	Token tk = gnext();
	index++;
	return tk;
}

/* 
	type :- type of Token we expect to be the next.
 */
bool Parser::expect(int type){
	if(!cnext()) return false;
	return tokens[index+1].type == type;
}

void Parser::handleKeyword(){
	Token tk = tokens[index];
	std::string skeyword = tk.data;
	std::cout << "Keyword : " << skeyword << std::endl;

	if (skeyword == "class"){
		
	}
	
	/* VARIABLE DECLARATION OR ASSIGNMENT */
	if (skeyword == "int"){
		
		/// int IDENTIFIER '=' expr
		
		std::cout << "int() -> " << tokens[index].data << std::endl;
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			 	fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		
		std::cout << "int() -> " << tokens[index].data << std::endl;
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		std::cout << "int() -> " << tokens[index].data << std::endl;
		index++;
		//Parse Expr
		Expression exp = parseExpr();
		
		std::cout << "int() -> " << "PARSING COMPLETED" << std::endl;
		return;
	}
	if (skeyword == "string"){
		
		/// string IDENTIFIER '=' expr 
		std::cout << "string() -> " << tokens[index].data << std::endl;
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		std::cout << "string() -> " << tokens[index].data << std::endl;
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		std::cout << "string() -> " << tokens[index].data << std::endl;
		index++;
		//Parse Expr
		Expression exp = parseExpr();
		std::cout << "string() -> " << "PARSING COMPLETED" << std::endl;
		return;
	}
	if (skeyword == "bool"){
		
		/// bool IDENTIFIER '=' expr 
		
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = IDENTIFIER
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = EQUAL
		index++; //current token = EXPRESSION
		//Parse Expr
		Expression exp = parseExpr();
	}
	if (skeyword == "float"){
		
		/// float IDENTIFIER '=' expr 
		
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		index++;
		//Parse Expr
	}
	if (skeyword == "return"){
		// return
		// return IDENTIFIER
	}
	if (skeyword == "for"){
		/* 
		
		important -> 
			object itr(...)
			increment i++
		
		for i, x in itr([x]):
			.......
		
		for x in [x]:
			.......
		
		*/
	}
	if (skeyword == "while"){
		/* 
		while exp:
			.......
		
		while true : [int i] ->
			.......
		*/
	}
	if (skeyword == "when"){
		/*	
		when(int i){ 
			exp1: {...}
			exp2: {...}
			else: {...}
		}
		
		when(int i){ [int i] ->
			it.x.doY() == exp2: {...}
			it.isZ: {...}
			exp1: {...}
			else: {...}
		}
		*/
		
	}
	if (skeyword == "fun"){
		
		///1) fun IDENTIFIER '(' ')' > RETURN_TYPE '{' expr '}'
		///2) fun IDENTIFIER '(' ')' > RETURN_TYPE  
		///		'{' expr '}'
		///3) fun IDENTIFIER '(' ')' '{' expr '}' //if void type no return type required
		
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = IDENTIFIER
		
		if(!expect(CIRCLEBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '(' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETSTART
		
		/* Parse Arguments */
		
		if(!expect(CIRCLEBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected ')' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETEND
		
		/* Parse Return Type */
		if(cnext() && !expect(CURLYBRACKETSTART)){
			//If next token is not  '{' there has to be '> RETURN_TYPE'
			if(!expect(LGREATER)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected '>' got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = LGREATER
		
			if(!expect(IDENTIFIER) && !expect(K_INT) || !expect(K_STRING) || !expect(K_BOOL)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected a Return type got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = IDENTIFIER or Data Type
			Token return_type_token = tokens[index];
		}
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		if(!expect(CURLYBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '{' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETSTART
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		/* Parse Function Body */
		std::vector<Expression> body; //TODO(USE Statement class)
		while(cnext() && expect(CIRCLEBRACKETEND)){
			index++;
			//Parse each line of function body
			if(expect(LINE_END)){
				//function body is on next line
				index++;
				continue;
			}
			body.push_back(parseExpr());
		}
				
		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
			
		if(!expect(CURLYBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '}' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETEND

	}
	if (skeyword == "if"){
		//if (exp) { exps }
	}
	if (skeyword == "else"){
		
	}
	if (skeyword == "del"){
		//del [IDENTIFIER](s)
	}
	if (skeyword == "as"){
		//del [IDENTIFIER](s)
	}
	if (skeyword == "using"){
		//del [IDENTIFIER](s)
	}

}

//TODO(Use Return type as pointers)
Expression Parser::parseExpr(int id){
	id++;

	if(tokens[index].type == LINE_END){
		fire_syntax_error("Parser cannot start from line ending.", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	
	//STRING EXPRESSION PARSING
	if(tokens[index].type == STRING){
		StringExprPoint str = parseStringExpr();
		Expression expstr(STRING_EXP);
		expstr.child.stringExp = str;
		return expstr;
	}
	
	//BOOL EXPRESSION PARSING
	if(tokens[index].type == BOOL){
		BoolExprPoint _bool = parseBoolExpr();
		Expression expbool(BOOL_EXP);
		expbool.child.boolExp = _bool;
		return expbool;
	}
	
	//INTEGER EXPRESSION PARSING
	if(tokens[index].type == INTEGER){
		NumberExprPoint num = parseIntExpr();
		Expression expnum(NUMBER_EXP);
		expnum.child.numExp = num;
		return expnum;
	}
}


StringExprPoint Parser::parseStringExpr(int id){
	
	if (tokens[index].type != STRING){
		Token current = tokens[index];
		fire_illegal_argument_error("Token at current index is not of type String but String was required got '"+current.data+"'", current.columnno, current.lineno, current.file_path);
	}

	std::string left = tokens[index].data;

	if(gnext().type == LINE_END || gnext().type == END_OF_FILE){
		StringExprPoint leftExp(left);
		leftExp.s2 = "";
		leftExp.str_op = STR_ADD;
		leftExp.sHasExpr = false;
		std::cout << "Creating string compiled\n";
		return leftExp;
	}
	
	if(!expect(PLUS) && !expect(STAR)){
		fire_syntax_error("Expected '+' '*' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	index++; //token = '+' or '*'

	char op = tokens[index].data[0];

	StringExprPoint right;
	while(tokens[index].type != LINE_END && cnext()){
		right = parseStringExpr();
		index++;
	}
	if(op == '+'){
		StringExprPoint exp(left);
		exp.se2 = &right;
		exp.str_op = STR_ADD;
		exp.sHasExpr = true;
		std::cout << "Returning String Expression with value ";
		exp.tree();
		std::cout << std::endl;
		return exp;
	}

	//NOT CURRENTLY SUPPORTED
	if(op == '*'){
		if(true){//right->type != NUMBER_EXP){
			index-=2;//TODO
			fire_syntax_error("Expected an int got '", gnext().columnno, gnext().lineno, gnext().file_path); //+ right.type);
		}
		// StringExprPoint expM(left);
		// exp.multiplier = right->child.numExp;
		// exp.op = STR_MUL;
		// exp.hasExpr = true;
		// std::cout << "Returning String Expression with value ";
		// exp.tree();
		// std::cout << std::endl;
		// return expM;
	}
}

BoolExprPoint Parser::parseBoolExpr(int id){
	if (tokens[index].type != BOOL){
		Token current = tokens[index];
		fire_illegal_argument_error("Token at current index is not of type Boolean but Boolean was required, got '"+current.data+"'", current.columnno, current.lineno, current.file_path);
	}
	BoolExprPoint left = string_to_bool(tokens[index].data);
	if (left.isnull){
		fire_syntax_error("Expected boolean ('true' 'false') value got '" + tokens[index].data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	
	if(gnext().type == LINE_END){
		BoolExprPoint exp(left);
		std::cout << "Returning Boolean Expression with value " << exp.value << std::endl;
		return exp;
	}else{
		fire_syntax_error("Operations not allowed on Boolean type.", gnext().columnno, gnext().lineno, gnext().file_path);
	}
}

NumberExprPoint Parser::parseIntExpr(int id){

	if (tokens[index].type != INTEGER){
		Token current = tokens[index];
		fire_illegal_argument_error("Token at current index is not of type Integer but Integer was required, got '"+current.data+"'", current.columnno, current.lineno, current.file_path);
	}

	std::cout << id << "] parseExpr() -> " << tokens[index].data << std::endl;
	
	int left = string_to_int(tokens[index].data);
	
	if(gnext().type == LINE_END){

		NumberExprPoint leftNumExp(left);
		leftNumExp.n2 = 0;
		leftNumExp.op = OP_ADD;
		leftNumExp.hasExpr = false;
		std::cout << "Returning Integer Expression with value " << leftNumExp.n1 << std::endl;
		return leftNumExp;
	
	}

	if(!expect(PLUS) && !expect(MINUS) && !expect(STAR) && !expect(RSLASH)){
		fire_syntax_error("Expected '+' '-' '*' '/' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	index++;
	
	num_operation op = get_op(tokens[index].type);
	index++;
	
	NumberExprPoint right;
	while(tokens[index].type != LINE_END && cnext()){
		std::cout << id << "] in while : " << tokens[index].to_string() << std::endl;
		right = parseIntExpr(id);
		std::cout << id << "] in while++";
		index++;
	}

	std::cout << id << "] out of while\n";
	right.tree();

	if(right.isnull){
		fire_syntax_error("Expected numeriacal expression got 'null'", gnext().columnno, gnext().lineno, gnext().file_path);
	}

	NumberExprPoint exp(left);
	exp.n2 = 0;
	exp.ne2 = &right;
	exp.hasExpr = true;
	exp.op = op;
	std::cout << "Returning Integer Expression with value ";
	exp.tree();
	std::cout << std::endl;
	return exp;
}

/* Get num_operation for token type. */
num_operation Parser::get_op(int type){
	switch(type){
		case PLUS: return OP_ADD;
		case MINUS: return OP_SUB;
		case RSLASH: return OP_DIV;
		case STAR: return OP_MUL;
		default:
			std::stringstream ss;
			ss << type;
			fire_syntax_error("Cannot convert type(=" + ss.str() +") to num_operation type.", gnext().columnno, gnext().lineno, gnext().file_path);
	}
}

void Parser::handleIdentifier(){
	Token tk = tokens[index];
	std::string sidentifier = tk.data;
	std::cout << "We Identifier : " << sidentifier << std::endl;
}

//REMOVE
bool Parser::hasNextToken(){
	return index < tokens.size() - 1;
}
