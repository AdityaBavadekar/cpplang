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

enum _stmnt_type_ {
	IF_STMNT, WHILE_STMNT, FOR_STMNT, WHEN_STMNT, TRY_STMNT, DELETE_STMNT, ASSIGN_STMNT
};

struct Statment{
	_stmnt_type_ type;
	union t{
		struct FunctionDef{};
		struct ClassDef{};
		struct Assign{};
		struct Try{};
		struct Return{};
		struct While{};
		struct For{};
		struct When{};
		struct Delete{};
		struct If{};
	};
	int lineno;
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

#define tp_identifier std::string

class AbstPrintable{
	public: virtual void tree() = 0;
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

enum expr_type {
	NUMBER_EXP=0,STRING_EXP=1,BOOL_EXP=2
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

struct ConstructorParam{
	tp_identifier name;
	tp_identifier type;
};

class FunctionStatement : public Null{
	public:
		tp_identifier name; 
		std::vector<Expression> body;
		std::vector<ConstructorParam> params;
		std::string return_type;
		void tree(){
			std::cout<< "FunctionStatment " << name << "("<< params.size() << " args){" << body.size() <<" exprs }" << std::endl;
		}
		FunctionStatement(tp_identifier _name):name(_name){};
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

#endif //AST_H