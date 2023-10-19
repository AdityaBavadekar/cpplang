#ifndef AST_H
#define AST_H
#include<iostream>
#include<vector>
#include<string>
#include "..\tokenizer\tokenizer.h"
using namespace std;

struct AST {
	std::string name;
	std::vector<AST> children;
	std::vector<Token> tokens;
	
	bool hasChildren(){
		return children.size() > 0;
	}
	bool hasTokens(){
		return tokens.size() > 0;
	}
};

enum expr_type {
	NUMBER_EXP=0,STRING_EXP=1,BOOL_EXP=2
};

enum num_operation {
	OP_ADD=0,
	OP_SUB=1,
	OP_DIV=2,
	OP_MUL=3,
};

enum string_op {
	STR_ADD=0,
	STR_MUL=1
};

enum access_modifier_type{
	ACCESS_PUBLIC = 0,
	ACCESS_PROTECTED = 1,
	ACCESS_PRIVATE = 2,
};

#define tp_identifier std::string

class AbstPrintable{
	public: virtual void tree() = 0;
};

struct Scope{
	std::string scope;
	Scope():scope("unk"){};
	Scope(std::string _scope):scope(scope){};
};

struct Null{
	/* 
	True represents null value
	False represents non-null value
	*/
	bool isnull;
	Null():isnull(true){};
	Null(bool b):isnull(b){};
};

struct ConstructorParam{
	tp_identifier name;
	tp_identifier type;
};

class NumberExprPoint : public Null, public AbstPrintable{
	public:
		int n1;
		/* If n2 is not present n2 = 0 and op = OP_ADD */
		int n2;
		bool hasExpr;
		num_operation op;
		NumberExprPoint* ne2;
		void tree(){
			std::cout<< "[NumberExpr " << n1 << "]";
			switch(op){
				case OP_ADD:{
					std::cout << " + ";
					break;
				}
				case OP_SUB:{
					std::cout << " - ";
					break;
				}
				case OP_DIV:{
					std::cout << " / ";
					break;
				}
				case OP_MUL:{
					std::cout << " * ";
					break;
				}
			}
			if(hasExpr && ne2 != nullptr) ne2->tree();
			if(!hasExpr) std::cout << "[" << n2 << "]" << std::endl;
		}
		NumberExprPoint(int primary): Null(false),n1(primary){};
		NumberExprPoint():Null(true){};
};

class StringExprPoint : public Null,public AbstPrintable{
	public:
		std::string s1;
		std::string s2;
		bool sHasExpr;
		string_op str_op;
		StringExprPoint* se2;
		NumberExprPoint* multiplier;
		void tree(){
			std::cout<< "[StringExpr '" << s1 << "']";
			switch(str_op){
				case STR_ADD:{
					std::cout << " + ";
					break;
				}
				case STR_MUL:{
					std::cout << " * ";
					break;
				}
			}
			if(sHasExpr && str_op == STR_ADD) se2->tree();
			if(sHasExpr && str_op == STR_MUL) multiplier->tree();
			else std::cout << "['" << s2 << "']" << std::endl;
		}
		StringExprPoint(std::string primary):Null(false),s1(primary),s2(""),multiplier(nullptr),se2(nullptr){};
		StringExprPoint():Null(true),s1(""),s2(""),str_op(STR_ADD),multiplier(nullptr),se2(nullptr){};
};

class BoolExprPoint : public Null,public AbstPrintable{
	public:
		bool value;
		void tree(){
			std::string v;
			if (value) v = "true";
			else v = "false";
			std::cout<< "[Boolean " << v << "]" << std::endl;
		}
		BoolExprPoint(bool v):Null(false),value(v){};
		BoolExprPoint():Null(true){};
};

class ListExprPoint : public Null,public AbstPrintable{
	public:
		//TODO
		void tree(){
			std::cout<< "[ListExprPoint]" << std::endl;
		}
		ListExprPoint():Null(false){};
};

class Expression : public Null{
	public:
		expr_type type;
		NumberExprPoint numExp;
		StringExprPoint stringExp; 
		BoolExprPoint boolExp;
		~Expression(){};
		void tree(){
			switch (type)
			{
			case NUMBER_EXP:
				numExp.tree();
				break;
			case STRING_EXP:
				stringExp.tree();
				break;
			case BOOL_EXP:
				boolExp.tree();
				break;
			default:
				break;
			}
		}
		Expression(expr_type _type): Null(false), type(_type){};
		Expression(): Null(true){};
};

class FunctionDef : public Null{
	public:
		tp_identifier name; 
		std::vector<Expression> body;
		std::vector<ConstructorParam> params;
		std::string return_type;
		/*
			fun IDENTIFIER(params) > RETURN_TYPE {
				//body expressions/statements
			}
		*/
		void tree(){
			std::cout<< "FunctionDef " << name << "-> " << return_type << " ("<< params.size() << " args){" << body.size() <<" exprs }" << std::endl;
		}
		FunctionDef(tp_identifier _name):name(_name){};
};

class ClassDef : public Null,public AbstPrintable{
	public:
		/* Access Modifiers */
		access_modifier_type access;
		
		/* Name of the class */
		tp_identifier name;
		
		/* Constructor Parameters */
		std::vector<ConstructorParam> params;

		/*   Parent classes 
			(May be use different class to also asign 
			access modifiers to inheritance)
		*/
		std::vector<tp_identifier> superclasses;

		/* 
			Functions defined inside this class.
			defaults are :-
				- init() //Initialise constructor function
				- clear() //Destroy destructor function
		*/
		//TODO("Use Function Statements not Definitions")
		std::vector<FunctionDef> innerFunctions;

		std::vector<Expression> body;
		/* 
			ACCESS_MODIFIER class IDENTIFIER : parent_classes {
				A) ---- assignments or declarations ----
				B) ---- functions ----
					init(){}
					clear(){}
					custom functions
				C) ---- complex statements (for latter) ----
			}
		*/

		void tree(){
			switch (access)
			{
				case ACCESS_PRIVATE:
					std::cout << "private";
					break;
				case ACCESS_PROTECTED:
					std::cout << "protected";
					break;
				case ACCESS_PUBLIC:
					std::cout << "public";
					break;
			}
			std::cout << " class " << name;
			std::cout << "(" << params.size() << ") ";
			if(superclasses.size() > 0){
				for (size_t i = 0; i < superclasses.size(); i++)
				{
					std::cout << superclasses[i];
					if(i < superclasses.size()-1) std::cout << ", ";
				}
			}else std::cout << "void ";
			std::cout << " { " << body.size() << " Exprs, " << innerFunctions.size() << " Funs } " << std::endl;
		}
		ClassDef(tp_identifier _name):Null(false), name(_name),access(ACCESS_PRIVATE){};
		ClassDef(tp_identifier _name, access_modifier_type _access):Null(false), name(_name),access(access){};
};

class Number: public Null{
	public:
		int n;
		Number():Null(),n(0){};
		Number(int _n):Null(false),n(_n){};
		Number operator+(Number other) const {
			return Number(n + other.n);
		}
		Number operator-(Number other) const {
			return Number(n - other.n);
		}
		Number operator/(Number other) const {
			return Number(n / other.n);
		}
		Number operator*(Number other) const {
			return Number(n * other.n);
		}
		Number operator+(int other) const {
			return Number(n + other);
		}
		Number operator-(int other) const {
			return Number(n - other);
		}
		Number operator/(int other) const {
			return Number(n / other);
		}
		Number operator*(int other) const {
			return Number(n * other);
		}
};

struct Statement{
	enum _stmnt_type_ {
		IF_STMNT, WHILE_STMNT, FOR_STMNT, WHEN_STMNT, TRY_STMNT, DELETE_STMNT, ASSIGN_STMNT
	};
	_stmnt_type_ type;
	union Structs{
		FunctionDef sFunDef;
		ClassDef sClassDef;
		struct Assign{
			tp_identifier varName;
			Expression exp;
			Assign(tp_identifier _varName):varName(_varName){};
		} sAssign;

		struct Try{
			std::vector<Statement*> body;
			std::vector<Statement*> onCatchStatements;
			ConstructorParam catchConstructor;
		} sTry;
		
		struct Return{
			enum return_stmnt_type{R_VOID=0, R_IDENTIFIER=1, R_EXPRESSION=2};
			return_stmnt_type type;
			union{
				tp_identifier identifier;
				Expression expression;
			};
			Return(return_stmnt_type _type):type(_type){};
		} sReturn;

		struct While{
			Expression condition;
			std::vector<Statement*> body;			
		} sWhile;
		struct For{

		} sFor;
		struct When{
			struct WhenElement{
				std::string caseValue;
				std::vector<Statement*> body;
			};
			std::vector<WhenElement*> elements;
			tp_identifier variable;
			When(tp_identifier _variable):variable(_variable){};
		} sWhen;
		struct Delete{
			std::vector<tp_identifier> identifiers;
		} sDelete;
		struct If{
			Expression condition;
			std::vector<Statement*> body;	
		} sIf;
	};
	Statement(_stmnt_type_ _type):type(_type){};
};
#endif //AST_H