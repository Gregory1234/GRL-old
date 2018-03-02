#include<iostream>
#include<stdio.h>
#include<fstream>
#include<structure.h>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
using namespace std;

string fn;

GRL::CompilerContext context;

int main(int argc,char* argv[]){
	context = GRL::CompilerContext();
	const char* outfn;
	for(int i = 1;i<argc;i++){
		fn=argv[i];
	}
	yyin=fopen(fn.c_str(),"r");
	context.scanForGlobals(fn);
	//cout << ifstream(argv[1]).rdbuf() << endl;
	yyparse();
}

void yyerror(const char* msg){
	cout << "\033[1;31mparsing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
}
void lexerror(const char* msg){
	cout << "\033[1;31mlexing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
}
