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

struct Null{
	/* 
	True represents null value
	False represents non-null value
	*/
	bool isnull;
	Null():isnull(true){};
	Null(bool b):isnull(b){};
};

class NumberExprPoint : public Null{
	public:
		int n1;
		/* If n2 is not present n2 = 0 and op = OP_ADD */
		int n2;
		bool hasExpr;
		num_operation op;
		NumberExprPoint* ne2;
		void tree(){
			std::cout<< "NumberExprPoint START" << std::endl;
			std::cout<< "Primary : "<< n1 << std::endl;
			std::cout<< "operation : " << op << std::endl;
			if(hasExpr){
				std::cout<< "Secondary : ";
				ne2->tree();
			}else std::cout << "Secondary : " << n2 << std::endl;
			std::cout<< "NumberExprPoint END" << std::endl;
		}
		NumberExprPoint(int primary): Null(false),n1(primary){};
		NumberExprPoint():Null(true){};
};

class StringExprPoint : public Null{
	public:
		std::string s1;
		std::string s2;
		bool sHasExpr;
		string_op str_op;
		StringExprPoint* se2;
		//NumberExprPoint* multiplier;
		void tree(){
			std::cout<< "StringExprPoint START" << std::endl;
			std::cout<< "Primary : "<< s1 << std::endl;
			std::cout<< "operation : " << str_op << std::endl;
			if(sHasExpr){
				std::cout<< "Secondary : ";
				se2->tree();
			}else std::cout << "Secondary : " << s2 << std::endl;
			std::cout<< "StringExprPoint END" << std::endl;
		}
		StringExprPoint(std::string primary):Null(false),s1(primary),s2(""),se2(nullptr){};
		StringExprPoint():Null(true),s1(""),s2(""),str_op(STR_ADD),se2(nullptr){};
};

class BoolExprPoint : public Null{
	public:
		bool value;
		void tree(){
			std::cout<< "Booleal value (" << value << ")" << std::endl;
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
		void tree(){
			std::cout<< "Main" << std::endl;
		}
		union Child {
			NumberExprPoint numExp;
			StringExprPoint stringExp; 
			BoolExprPoint boolExp;
			~Child(){};
			Child(){};
			Child(int type){
				std::cout << "Creating Child\n";
				switch(type){
					case NUMBER_EXP:{
						numExp = NumberExprPoint();
						break;
					}
					case STRING_EXP:{
						stringExp = StringExprPoint();
						break;
					}
					case BOOL_EXP:{
						boolExp = BoolExprPoint();
						break;
					}
				}
			};
			Child(const Expression &ex){
				Child ch;
				if(ex.type == NUMBER_EXP) ch.numExp = ex.child.numExp;
				if(ex.type == STRING_EXP) ch.stringExp = ex.child.stringExp;
				if(ex.type == BOOL_EXP) ch.boolExp = ex.child.boolExp;
			}
			
		};
		Child child;
		~Expression(){};
		Expression operator=(const Expression &ex){
			Expression new_ex(ex.type);
			if(ex.type == NUMBER_EXP) new_ex.child.numExp = ex.child.numExp;
			if(ex.type == STRING_EXP) new_ex.child.stringExp = ex.child.stringExp;
			if(ex.type == BOOL_EXP) new_ex.child.boolExp = ex.child.boolExp;
			return new_ex;
		}
		Expression(const Expression &ex):type(ex.type),child(ex){};
		Expression(expr_type _type): Null(false), type(_type), child(type){};
		Expression(): Null(true){};
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