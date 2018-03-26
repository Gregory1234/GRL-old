#include<iostream>
#include<stdio.h>
#include<fstream>
#include<inputs.h>
#include<structure.h>
#include<context.h>
#include<errors.h>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
extern void getDefault(GRL::CompilerContext&);
using namespace std;
int haserrors = 0;

string currentfn;
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
	currentfn = in.in;
	context.findGlobals(currentfn);
	if(haserrors){
		if(in.experr==0)
			return haserrors;
		else if(haserrors==in.experr)
			return 0;
		else
			return haserrors;
	}
	//cout << ifstream(argv[1]).rdbuf() << endl;
	currentfn = in.in;
	yyin=fopen(currentfn.c_str(),"r");
	yyparse();
	if(in.experr==0)
		return haserrors;
	else if(haserrors==in.experr)
		return 0;
	else if(haserrors==0)
		return UNDETECTED_ERROR_ERROR;
	else
		return haserrors;
}

void yyerror(const char* msg){
	cout << "\033[1;31mparsing error:\033[0m in " << currentfn << " line " << yylineno << endl << msg << endl;
	haserrors=context.stage==GRL_STAGE_GLOBALS?GLOBAL_FINDING_PARSER_ERROR:PARSING_ERROR;
}
void lexerror(const char* msg){
	cout << "\033[1;31mlexing error:\033[0m in " << currentfn << " line " << yylineno << endl << msg << endl;
	haserrors=LEXER_ERROR;
}
void inerror(const char* msg){
	cout << "\033[1;31minput error\033[0m" << endl << msg << endl;
	haserrors = INPUT_ERROR;
}
void othererror(const char* type,const char* msg,int ret){
	cout << "\033[1;31m" << type << " error" << "\033[0m in " << currentfn << " line " << yylineno << endl << msg << std::endl;
	haserrors = ret;
}
