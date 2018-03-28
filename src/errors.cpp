#include <iostream>
#include <errors.h>
#include <context.h>
int haserrors = 0;
extern int yylineno;
using namespace std;
extern string currentfn;

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
void othererror(const char* type, const char* msg, int ret){
	cout << "\033[1;31m" << type << " error" << "\033[0m in " << currentfn << " line " << yylineno << endl << msg << std::endl;
	haserrors = ret;
}
