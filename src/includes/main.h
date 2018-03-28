#ifndef GRL_MAIN_H
#define GRL_MAIN_H
#include <stdio.h>
#include <context.h>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
extern void getDefault(GRL::CompilerContext&);
extern int yydebug;
#endif //GRL_MAIN_H
