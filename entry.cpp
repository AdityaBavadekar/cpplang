#include<iostream>
#include<string>
#include "tokenizer/tokenizer.h"
#include "helpers/helpers.h"
using namespace std;

const std::string VERSION = "1.0.0";
void usage(){
	std::cout << "\n		Lang [v" << VERSION << "]\n\n";
	std::cout << "Usage: [file path][OPTIONS]\n\n";
	std::cout << "	OPTIONS:		Description\n";
	std::cout << "	--v			See VERSION\n";
	std::cout << "	--d			Start in Debug Mode\n";
	std::cout << "	--h			Help\n";
	std::cout << "\n" << std::endl;
	sysexit();
}

int main(int argc, char *argv[]){
	if(argc == 1){
		usage();
	}
	
	std::string path = argv[1];
	tokenizer_Main(path);
	
	system("PAUSE");
	return 0;
}