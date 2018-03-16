%defines
%code requires{
#include<structure.h>
extern GRL::CompilerContext context;
}
%{
#include<string>
#include<iostream>
void yyerror(const char*);
int yylex();
#define YYDEBUG 1
%}
%code requires{

#include<string>
}
%union{
	GRL::GRLType* type;
	std::string* str;
	int numI;
	char numC;
	GRL::Function* fun;
}

%token CLASS "class" NOCLASS "noclass"
%token END 0 "end of file"
%token<type> VOID_T "void" BYTE_T "byte" CHAR_T "char" SHORT_T "short" INT_T "int" LONG_T "long" UNSIGNED "unsigned"
%token<type> BOOL_T "bool" FLOAT_T "float" DOUBLE_T "double"
%token PUBLIC_MOD "public" PRIVATE_MOD "private" STATIC_MOD "static"
%token<str> STRING_C "string constant"
%token<str> IDENT "identifier"
%token<numI> INT_C "integer constant"
%token<numC> CHAR_C "char constant"
%type<type> typeident
%type<fun> fundef
%type<fun> funcall
%define parse.error verbose
%start input

%%

input:			classdef END
;

classdef:		CLASS IDENT {
	if(context.stage==GRL_STAGE_GLOBALS) {context.classes.push_back(GRL::Class(*$2));}
} '{' classcont '}'
|			NOCLASS '{' classcont '}'
;
classcont:		%empty
|			classcont fundef
|			classcont fielddef
;
fundef:			modifiers typeident IDENT '(' fundefargs ')' {
	if(context.stage==GRL_STAGE_GLOBALS) {
		context.functions.push_back(GRL::Function(*$3,*$2));
	}
} explicitcodeblock {$$=new GRL::Function(*$3,*$2);}
;
codeblock:		explicitcodeblock
|			codeline
;
explicitcodeblock:	'{' codelines '}'
;
codelines:		codelines codeline
|			codeline
;
fundefargs:		%empty
|			noemptyfundefargs
;
noemptyfundefargs:	fundefarg
|			noemptyfundefargs ',' fundefarg
;
fundefarg:		typeident IDENT
;
fielddef:		modifiers typeident IDENT ';'
;

typeident:		IDENT {
	if(context.stage==GRL_STAGE_COMPILING){
		if(context.getIdentifier(*$1,GRL::Identifier::CLASS).type==GRL::Identifier::NOTHING){
			YYERROR;
		}
	}
	$$=new GRL::GRLType(*$1);
}
|			typeident '[' ']' {$$=new GRL::GRLType(*$1);}
|			VOID_T {$$=new GRL::GRLType(std::string("void"));}
|			BOOL_T {$$=new GRL::GRLType(std::string("bool"));}
|			FLOAT_T {$$=new GRL::GRLType(std::string("float"));}
|			DOUBLE_T {$$=new GRL::GRLType(std::string("double"));}
|			BYTE_T {$$=new GRL::GRLType(std::string("byte"));}
|			CHAR_T {$$=new GRL::GRLType(std::string("char"));}
|			SHORT_T {$$=new GRL::GRLType(std::string("short"));}
|			INT_T {$$=new GRL::GRLType(std::string("int"));}
|			LONG_T {$$=new GRL::GRLType(std::string("long"));}
|			UNSIGNED BYTE_T {$$=new GRL::GRLType(std::string("unsigned byte"));}
|			UNSIGNED SHORT_T {$$=new GRL::GRLType(std::string("unsigned short"));}
|			UNSIGNED INT_T {$$=new GRL::GRLType(std::string("unsigned int"));}
|			UNSIGNED LONG_T {$$=new GRL::GRLType(std::string("unsigned long"));}
;

modifiers:		publicity_mod other_mod
;
publicity_mod:		"public"
|			"private"
|			%empty
;
other_mod:		%empty
|			other_mod "static"
;

codeline:		expression ';'
;
expression:		funcall
|			STRING_C
|			CHAR_C
|			INT_C
;
funcall:		IDENT '(' funcallargs ')' {
	if(context.stage==GRL_STAGE_COMPILING){
		if(context.getIdentifier(*$1,GRL::Identifier::FUNCTION).type==GRL::Identifier::NOTHING){
			YYERROR;
		}
	}
	$$=(GRL::Function*)context.getIdentifier(*$1,GRL::Identifier::FUNCTION).owner;
}
;
funcallargs:		noemptyfuncallargs
|			%empty
;
noemptyfuncallargs:	noemptyfuncallargs ',' expression
|			expression
;
%%
