#include<iostream>
#include<stdio.h>
#include<fstream>
#include<inputs.h>
#include<structure.h>
#include<errors.h>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
extern void getDefault(GRL::CompilerContext&);
using namespace std;
int haserrors = 0;

string fn;
extern int yydebug;
GRL::CompilerContext context;

int main(int argc,char* argv[]){
	GRL::input in(argc,argv);
	if(haserrors)
		return haserrors;
	if(in.debug)
		yydebug=1;
	context = GRL::CompilerContext();
	getDefault(context);
	fn = in.in;
	context.findGlobals(fn);
	if(haserrors)
		return haserrors;
	yyin=fopen(fn.c_str(),"r");
	//cout << ifstream(argv[1]).rdbuf() << endl;
	fn = in.in;
	yyparse();
	return haserrors;
}

void yyerror(const char* msg){
	cout << "\033[1;31mparsing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
	haserrors=context.stage==GRL_STAGE_GLOBALS?GLOBAL_FINDING_PARSER_ERROR:PARSING_ERROR;
}
void lexerror(const char* msg){
	cout << "\033[1;31mlexing error:\033[0m in " << fn << " line " << yylineno << endl << msg << endl;
	haserrors=LEXER_ERROR;
}
void inerror(const char* msg){
	std::cout << "\033[1;31minput error\033[0m" << std::endl << msg << std::endl;
	haserrors = INPUT_ERROR;
}
