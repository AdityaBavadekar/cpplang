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

#define LOG_TOKEN(msg) std::cout << __LINE__ << " Current Token : " << tokens[index].to_string();\
	std::cout << "\t-MSG:" << msg << std::endl;
Parser::Parser(std::vector<Token> _tokens, std::vector<Expression>* _returnExprs, std::vector<Statement*>* _stmnts) : tokens(_tokens), returnExpressions(_returnExprs), stmnts(_stmnts), index(0),logger("Parser"){}

void Parser::parse(){
	_parse();
}

void Parser::_parse(){
	std::cout << "Parsing..." << std::endl;
	while(hasNextToken()){
		Token tk = tokens[index];
		LOG_TOKEN("Parser Loop Token");
		
		if(tk.type == END_OF_FILE) break;
		
		if(tk.type >= TOKEN_KEYWORD_START && tk.type <= TOKEN_KEYWORD_END)	handleKeyword(returnExpressions);
		
		if(tk.type == IDENTIFIER) handleIdentifier();
		
		index++;
	}
	std::cout << "******* Tokens Parsed without Errors ******* " << std::endl;
}


void Parser::skipCircularBracketStart(){
	if(cnext() && gnext().type == CIRCLEBRACKETSTART) index++;
}

void Parser::skipCircularBracketEnd(){
	if(cnext() && gnext().type == CIRCLEBRACKETSTART) index++;
}

void Parser::skipSemiColon(){
	if(cnext() && gnext().type == SEMI) index++;
}

/* 
	Returns has next token or not.
 */
bool Parser::cnext(){
	return index < tokens.size() - 1;
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

void Parser::addExpression(Expression exp, std::vector<Expression>* returnExprs = nullptr){
	if(returnExprs == nullptr) returnExpressions->push_back(exp);
	else returnExprs->push_back(exp);
}

void Parser::addStatement(Statement exp, std::vector<Statement*>* stmntSptrs = nullptr){
	if(stmntSptrs == nullptr) stmntSptrs->push_back(&exp);
	else stmntSptrs->push_back(&exp);
}

void Parser::handleKeyword(std::vector<Expression>* returnExprs = nullptr){
	Token tk = tokens[index];
	std::string skeyword = tk.data;
	LOG_TOKEN("Keyword Token");

	if (tk.type == K_PUBLIC || tk.type == K_PRIVATE || tk.type == K_PROTECTED){
		switch (gnext().type) //gnext() throws error if there no next Token
		{
			case K_CLASS:
				index++;
				handleKeyword(returnExprs);
				break;
			default:
				fire_syntax_error("Expected 'class' after access modifier got '" + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
				break;
		}
	}

	if (skeyword == "class"){
		//Previous token mostly will be an access modifier
		access_modifier_type access;
		if(index != 0){
			Token tk = tokens[index-1]; 
			switch (tk.type)
			{
				case K_PUBLIC:
					access = ACCESS_PUBLIC;
					break;
				case K_PRIVATE:
					access = ACCESS_PRIVATE;
					break;
				case K_PROTECTED:
					access = ACCESS_PROTECTED;
					break;
				default:
					break;
			}
		}else{
			//Default would be Private
			access = ACCESS_PRIVATE;
		}

		/* 
			ACCESS_MODIFIER class IDENTIFIER > parent_classes {
				A) ---- assignments or declarations ----
				B) ---- functions ----
					init(){}
					clear(){}
					custom functions
				C) ---- complex statements (for latter) ----
			}
		*/
		
		LOG_TOKEN("Keyword.class Token before Identifier");
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = IDENTIFIER
		
		LOG_TOKEN("Keyword.class Token after Identifier");
		ClassDef cdef(tokens[index].data, access);

		LOG_TOKEN("Keyword.class Token before '('");
		if(!expect(CIRCLEBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '(' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETSTART
		
		/* Parse Arguments */
		cdef.params.clear(); //As Params are not supported for now TODO()
		
		LOG_TOKEN("Keyword.class Token before ')'");
		if(!expect(CIRCLEBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected ')' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETEND
		
		LOG_TOKEN("Keyword.class Token before Superclasses '>' ");
		/* Parse Superclasses */
		if(cnext() && !expect(CURLYBRACKETSTART)){
			//If next token is not  '{' there has to be superclass assigned
			if(!expect(LGREATER)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected '>' got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = LGREATER
		
			LOG_TOKEN("Keyword.class Token before Superclasses");
			if(!expect(IDENTIFIER)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected a superclass identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = IDENTIFIER or Data Type
			std::string superclass_name = tokens[index].data;
			cdef.superclasses.push_back(superclass_name);
			std::cout << "Saved superclass '" << superclass_name << std::endl;

			while (cnext() && !expect(LINE_END) && !expect(CURLYBRACKETSTART))
			{

				bool commaNeeded = index+2 < tokens.size() && tokens[index+2].type == IDENTIFIER;
				if(commaNeeded){
					if(!expect(COMMA)){
						if(!cnext()) gnext(); //Throws error in the method itself
						fire_syntax_error("Expected a ',' before superclass name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);		
					}
					index++; //token = ','
				}
				
				if(!expect(IDENTIFIER)){
					if(!cnext()) gnext(); //Throws error in the method itself
					fire_syntax_error("Expected a superclass identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
				}
				index++; //current token = IDENTIFIER or Data Type
				superclass_name = tokens[index].data;
				cdef.superclasses.push_back(superclass_name);
				std::cout << "Saved superclass '" << superclass_name << std::endl;
			}
		}
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		LOG_TOKEN("Keyword.class Token before '{'");
		if(!expect(CURLYBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '{' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETSTART
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;//current token = LINE_END
		}

		/* Parse Class Body */
		while(cnext() && !expect(CURLYBRACKETEND)){
			LOG_TOKEN("Keyword.class Token from While before increment");
			index++;
			//Parse each line of function body
			if(tokens[index].type == LINE_END){
				std::cout<<"Skipping Line ending\n";
				//function body is on next line
				continue;
			}
			handleKeyword(&cdef.body);
			std::cout << index << "] Parsed Exp > Exps : " << cdef.body.size() << std::endl;
			LOG_TOKEN("Keyword.class Token from While after increment");
			cdef.tree();
		}

		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		LOG_TOKEN("Keyword.class Token before '}'");
		if(!expect(CURLYBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '}' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETEND

		LOG_TOKEN("Keyword.class Token completion");
		std::cout << "class() : PARSED" << std::endl;
		cdef.tree();
	}
	
	/* VARIABLE DECLARATION OR ASSIGNMENT */
	if (skeyword == "int"){

		/// int IDENTIFIER '=' expr

		LOG_TOKEN("Keyword.int Token before Identifier");
		std::cout << "int() -> " << tokens[index].data << std::endl;
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			 	fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		std::string name = tokens[index].data;
		Statement::Structs::Assign intAssign(name);
		Statement::Structs::Assign intTest(name);
		LOG_TOKEN("Keyword.int Token after Identifier");
		
		LOG_TOKEN("Keyword.int Token before Equal");
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		
		LOG_TOKEN("Keyword.int Token after Equal.1");
		index++;
		
		LOG_TOKEN("Keyword.int Token after Equal.2");
		//Parse Expr
		Expression exp = parseExpr();
		intAssign.exp = exp;
		LOG_TOKEN("Keyword.int Token after parseExpr");
		addExpression(exp, returnExprs);
		std::cout << "int() -> " << "PARSING COMPLETED" << std::endl;
		return;
	}
	if (skeyword == "string"){
		
		/// string IDENTIFIER '=' expr 
		LOG_TOKEN("Keyword.string Token before Identifier");
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		std::string name = tokens[index].data;
		LOG_TOKEN("Keyword.string Token after Identifier");
		if(!expect(EQUAL)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '=' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		
		LOG_TOKEN("Keyword.string Token after Equal.1");
		index++;
		
		LOG_TOKEN("Keyword.string Token after Equal.2");
		//Parse Expr
		Expression exp = parseExpr();
		
		LOG_TOKEN("Keyword.string Token after parseExpr");
		addExpression(exp, returnExprs);
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
		addExpression(exp, returnExprs);
		std::cout << "bool() -> " << "PARSING COMPLETED" << std::endl;
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

		//Parse Expr TODO()
	}
	if (skeyword == "return"){
		index++;// currentToken = return
		std::vector<Expression> exprs;
		while(!expect(LINE_END) && cnext()){
			Expression e = (parseExpr());
			if(!e.isnull) exprs.push_back(e);
			else{
				Token current  = tokens[index];
				if(!current.type == IDENTIFIER){
					fire_syntax_error("Expected an expression or identifier, got '" + current.data + "'", current.columnno, current.lineno, current.file_path);
				}else{
					// Expression ex(TYPE_IDENTIFIER);
					// exprs.push_back() TODO()
				}
			}
			index++;
		}
		std::cout << "Return statement parsed.\n";
		return;
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
		bool traverseMode = false;
		std::string name1(""), name2("");
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;
		name1 = tokens[index].data;
		if(index+2 < tokens.size() && tokens[index+2].type == IDENTIFIER){
			if(!expect(COMMA)){
				fire_syntax_error("Expected ',' before '" + tokens[index+2].data + "' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
			}else{
				traverseMode = true;
				index++;// token = ','
				index++;// token = IDENTIFIER
				name2 = tokens[index].data;
			}
		}
	
		if(!expect(K_IN)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected 'in' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++;//token = in
		
		if(traverseMode){
			//expect traverse(array)	
		}else{
			//expect range(x1, x2)
			//expect range(x2)
			//expect array
		}
		//index++;//
		
		//Temp loop to skip iterator part
		while(cnext() && !expect(CURLYBRACKETSTART) && !expect(LINE_END)){
			index++;
		}

		if(!expect(CURLYBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '{' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETSTART
		
		/* Parse For Loop Body */
		//Temp loop to skip body/block part
		while(cnext() && !expect(CURLYBRACKETEND)){
			index++;
		}
		
		if(!expect(CURLYBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '}' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETEND
		
		LOG_TOKEN("Keyword.for PARSED");
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
		
		LOG_TOKEN("Keyword.fun Token before Identifier");
		if(!expect(IDENTIFIER)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = IDENTIFIER
		
		LOG_TOKEN("Keyword.fun Token after Identifier");
		FunctionDef fdef(tokens[index].data);

		LOG_TOKEN("Keyword.fun Token before '('");
		if(!expect(CIRCLEBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '(' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETSTART
		
		/* Parse Arguments */
		fdef.params.clear(); //As Params are not supported for now TODO()
		
		LOG_TOKEN("Keyword.fun Token before ')'");
		if(!expect(CIRCLEBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected ')' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CIRCLEBRACKETEND
		
		LOG_TOKEN("Keyword.fun Token before Return Type");
		/* Parse Return Type */
		if(cnext() && !expect(CURLYBRACKETSTART)){
			//If next token is not  '{' there has to be '> RETURN_TYPE'
			if(!expect(LGREATER)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected '>' got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = LGREATER
		
			LOG_TOKEN("Keyword.fun Token before Return Identifier");
			if(!expect(IDENTIFIER) && !expect(K_INT) && !expect(K_STRING) && !expect(K_BOOL)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected return type got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++; //current token = IDENTIFIER or Data Type
			Token return_type_token = tokens[index];
			fdef.return_type = return_type_token.data;
		}else fdef.return_type = "void";
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		LOG_TOKEN("Keyword.fun Token before '{'");
		if(!expect(CURLYBRACKETSTART)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '{' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETSTART
		
		if(expect(LINE_END)){
			//function body is on next line
			index++;//current token = LINE_END
		}

		/* Parse Function Body */
		while(cnext() && !expect(CURLYBRACKETEND)){
			LOG_TOKEN("Keyword.fun Token from While before increment");
			index++;
			//Parse each line of function body
			if(expect(LINE_END)){
				std::cout<<"Skipping Line ending\n";
				//function body is on next line
				index++;
				continue;
			}
			handleKeyword(&fdef.body);
			std::cout << index << "] Parsed Exp > Exps : " << fdef.body.size() << std::endl;
			LOG_TOKEN("Keyword.fun Token from While after increment");
		}

		if(expect(LINE_END)){
			//function body is on next line
			index++;
		}
		
		LOG_TOKEN("Keyword.fun Token before '}'");
		if(!expect(CURLYBRACKETEND)){
			if(!cnext()) gnext(); //Throws error in the method itself
			fire_syntax_error("Expected '}' or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
		}
		index++; //current token = CURLYBRACKETEND

		LOG_TOKEN("Keyword.fun Token completion");
		std::cout << "function() : PARSED" << std::endl;
		fdef.tree();
	}
	if (skeyword == "if"){
		//if (exp) { exps }
	}
	if (skeyword == "else"){
		
	}
	if (skeyword == "delete"){
		//del [IDENTIFIER](s)
		LOG_TOKEN("Keyword.delete Token before Identifier");
		std::vector<tp_identifier> names;
		int i = -1;
		while (!expect(LINE_END) && cnext())
		{
			i++; //Required to decide whether a Comma is needed or not.
			//Incase of first iteration and last there should be 'no' comma 
			//Eg: del num, r
			if(i!=0){
				if(!expect(COMMA) && index+2 < tokens.size() && tokens[index+2].type == IDENTIFIER){
					if(!cnext()) gnext(); //Throws error in the method itself
					fire_syntax_error("Expected a ',' before Idenntifier got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);		
				}
				index++; //token = ','
			}

			if(!expect(IDENTIFIER)){
				if(!cnext()) gnext(); //Throws error in the method itself
				fire_syntax_error("Expected Identifier or name got " + gnext().data, gnext().columnno, gnext().lineno, gnext().file_path);
			}
			index++;
			names.push_back(tokens[index].data);
			LOG_TOKEN("Keyword.delete Token after while iteration.")
		}
		LOG_TOKEN("Keyword.delete Token after completion")
		std::cout << "Delete (" << names.size() << ")" << std::endl;
	}
	if (skeyword == "as"){
		//[IDENTIFIER as IDENTIFIER
	}
	if (skeyword == "using"){
		//UNKNOWN SYNTAX
	}
}

//TODO(Use Return type as pointers)
Expression Parser::parseExpr(int id){
	id++;

	LOG_TOKEN("ParseExpr Token on called");
	if(tokens[index].type == LINE_END){
		fire_syntax_error("Parser cannot start from line ending.", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	
	//STRING EXPRESSION PARSING
	if(tokens[index].type == STRING){
		StringExprPoint str = parseStringExpr();
		Expression expstr(STRING_EXP);
		expstr.stringExp = str;
		return expstr;
	}
	
	//BOOL EXPRESSION PARSING
	if(tokens[index].type == K_FALSE || tokens[index].type == K_TRUE ){
		BoolExprPoint _bool = parseBoolExpr();
		Expression expbool(BOOL_EXP);
		expbool.boolExp = _bool;
		return expbool;
	}
	
	//INTEGER EXPRESSION PARSING
	if(tokens[index].type == INTEGER){
		NumberExprPoint num = parseIntExpr();
		Expression expnum(NUMBER_EXP);
		expnum.numExp = num;
		return expnum;
	}
	Expression nullVal;
	return nullVal;
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
		std::cout << "Returning String Expression with simple value." << std::endl;
		return leftExp;
	}
	
	if(!expect(PLUS) && !expect(STAR)){
		fire_syntax_error("Expected '+' '*' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	
	index++; //token = '+' or '*'
	index++;

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
		std::cout << "Returning String Expression with complex value." << std::endl;
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
	if (tokens[index].type != K_FALSE && tokens[index].type != K_TRUE){
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

	LOG_TOKEN("ParseINTExpr Token on called");
	if (tokens[index].type != INTEGER){
		Token current = tokens[index];
		fire_illegal_argument_error("Token at current index is not of type Integer but Integer was required, got '"+current.data+"'", current.columnno, current.lineno, current.file_path);
	}

	std::cout << id << "] parseExpr() -> " << tokens[index].data << std::endl;
	
	int left = string_to_int(tokens[index].data);
	
	if(gnext().type == LINE_END){
		NumberExprPoint leftNumExp(left);
		leftNumExp.n2 = 0;
		leftNumExp.ne2 = nullptr;
		leftNumExp.op = OP_ADD;
		leftNumExp.hasExpr = false;
		std::cout << "Returning Integer Expression with simple value." << std::endl;
		return leftNumExp;
	}

	if(!expect(PLUS) && !expect(MINUS) && !expect(STAR) && !expect(RSLASH)){
		fire_syntax_error("Expected '+' '-' '*' '/' got '" + gnext().data + "'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	index++;
	
	LOG_TOKEN("ParseINTExpr Token after expect operator");
	num_operation op = get_op(tokens[index].type);
	index++;
	
	LOG_TOKEN("ParseINTExpr Token increment");
	NumberExprPoint right;
	while(tokens[index].type != LINE_END && cnext()){
		right = parseIntExpr(id);
		if(tokens[index].type == LINE_END) break;
		index++;
		LOG_TOKEN("ParseINTExpr Token after While Increment");
	}

	LOG_TOKEN("ParseINTExpr Token after While.completed");
	if(right.isnull){
		fire_syntax_error("Expected numeriacal expression got 'null'", gnext().columnno, gnext().lineno, gnext().file_path);
	}
	int n2 = 0;
	if (op == OP_MUL) n2 = 1;
	NumberExprPoint exp(left);
	exp.n2 = n2;
	exp.ne2 = &right;
	exp.hasExpr = true;
	exp.op = op;
	std::cout << "Returning Integer Expression with complex value.";
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
