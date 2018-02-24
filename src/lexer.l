%{
#include "parser.h"
extern int yylineno;
#include <string>
void yyerror(const char*);
%}
%option noyywrap
%%

"class"				return CLASS;
"noclass"			return NOCLASS;

("("|")"|"{"|"}"|"["|"]"|"<"|">")	return yytext[0];

"void"				return VOID_T;
("byte"|"int8")			return BYTE_T;
"char"				return CHAR_T;
("int"|"int32"|"dword"|"double word")		return INT_T;
("long"|"int64"|"qword"|"quadruple word")	return LONG_T;
("short"|"int16"|"word")	return SHORT_T;
"unsigned"			return UNSIGNED;
("bool"|"boolen")		return BOOL_T;
"float"				return FLOAT_T;
"double"			return DOUBLE_T;

"public"			return PUBLIC_MOD;
"private"			return PRIVATE_MOD;
"static"			return STATIC_MOD;

[a-zA-Z_][a-zA-Z_0-9]*		{yylval.str=new std::string(yytext); return IDENT;}
[0-9]+				{yylval.numI=atoi(yytext); return INT_C;}
\".*\"				{yylval.str=new std::string(std::string(yytext).substr(1,strlen(yytext)-2)); return STRING_C;}
\'.\'				{yylval.str=(new std::string("")+yytext[1]); return CHAR_C;}

[ \t]				{}
\n				{yylineno++;}
.				{yyerror((std::string("Unknown character encountered!")+yytext).c_str());}

%%
