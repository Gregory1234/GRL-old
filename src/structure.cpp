#include<structure.h>
extern GRL::CompilerContext context;
extern FILE* yyin;
extern int yyparse();
void scanFile(std::string filename){
	context.globalfinding=true;
	yyin=fopen(filename.c_str(),"r");
	yyparse();
	context.globalfinding=false;
}

namespace GRL{
	Identifier notFound = Identifier();
}
