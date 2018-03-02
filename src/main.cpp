#include<iostream>
#include<stdio.h>
#include<fstream>
#include<structure.h>
#include<inputs.h>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
extern void getDefault(GRL::CompilerContext&);
using namespace std;

string fn;
extern int yydebug;
GRL::CompilerContext context;

int main(int argc,char* argv[]){
	GRL::input in(argc,argv);
	if(in.debug)
		yydebug=1;
	context = GRL::CompilerContext();
	getDefault(context);
	fn = in.in;
	context.scanForGlobals(fn);
	yyin=fopen(fn.c_str(),"r");
	//cout << ifstream(argv[1]).rdbuf() << endl;
	fn = in.in;
	yyparse();
}

void yyerror(const char* msg){
	cout << "\033[1;31mparsing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
}
void lexerror(const char* msg){
	cout << "\033[1;31mlexing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
}
