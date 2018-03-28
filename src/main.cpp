#include <fstream>
#include <iostream>
#include <inputs.h>
#include <structure.h>
#include <context.h>
#include <main.h>
#include <errors.h>

using namespace std;

string currentfn;

int main(int argc, char* argv[]){
	GRL::input in(argc,argv);
	if(haserrors)
		return haserrors;
	if(in.debug)
		yydebug=1;
	getDefault(context);
	currentfn = in.in;
	context.findGlobals(currentfn);
	if(in.experr==0)
		return haserrors;
	else if(haserrors==in.experr)
		return 0;
	else if(haserrors)
		return haserrors;
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
