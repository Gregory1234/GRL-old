#include<structure.h>
#include<context.h>
extern GRL::CompilerContext context;
extern FILE* yyin;
extern int yyparse();
extern std::string fn;
void scanFile(std::string filename){
	fn=filename;
	context.globalfinding=true;
	yyin=fopen(filename.c_str(),"r");
	yyparse();
	context.globalfinding=false;
}

namespace GRL{
	Identifier notFound = Identifier();
}
