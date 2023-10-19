#include<iostream>
#include<string>
#include "tokenizer/tokenizer.h"
#include "helpers/helpers.h"
#include "ast/ast.h"
#include "helpers/errors.h"
#include "inter/interactive.h"
#include "parser/parser.h"
using namespace std;

const std::string VERSION = "1.0.1";
void usage(){
	std::cout << "\n\tLang " << VERSION << "\n\n";
	std::cout << "Usage:\n";
	std::cout << "\t main <file> [options]\n";
	std::cout << "  Options:\n";
	std::cout << "	--v           Display Version.\n";
	std::cout << "	--d           Start in Debug Mode.\n";
	std::cout << "	--h           Show Help.\n";
	std::cout << "	--i           Start in interactive mode.\n";
	std::cout << "\n" << std::endl;
	exit(0);
}

int main(int argc, char *argv[]){
	if(argc == 1){
		usage();
	}
	bool debug = false;
	std::string arg1 = argv[1];
	
	if(arg1.length() == 3 && arg1[0] == '-' && arg1[1] == '-'){
		switch(arg1[2]){
			case 'v':
				std::cout << "Lang v" << VERSION << std::endl;
				return 0;
				break;
			case 'd':
				debug = true;
				break;
			case 'h':
				usage();
				break;
			case 'i':
				//--i
				interactive_Main();
				return 0;
			default: break;
		}
	}
	
	std::string path = argv[1];
	std::vector<Token> tokens = tokenizer_Main(path);
	std::vector<Expression> exprs;
	std::vector<Statement*> stmnts;
	Parser parser = Parser(tokens, &exprs, &stmnts); //TODO(Use Pointer for Tokens)
	parser.parse();
	std::cout << "\n--- ALL PARSING COMPLETED ---"<< std::endl;
	for (size_t i = 0; i < exprs.size(); i++)
	{
		exprs[i].tree();
	}
	
	return 0;
}