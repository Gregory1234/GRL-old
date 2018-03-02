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
	std::string* str;
	int numI;
	char numC;
}

%token CLASS "class" NOCLASS "noclass"
%token END 0 "end of file"
%token VOID_T "void" BYTE_T "byte" CHAR_T "char" SHORT_T "short" INT_T "int" LONG_T "long" UNSIGNED "unsigned"
%token BOOL_T "bool" FLOAT_T "float" DOUBLE_T "double"
%token PUBLIC_MOD "public" PRIVATE_MOD "private" STATIC_MOD "static"
%token<str> STRING_C "string constant"
%token<str> IDENT "identifier"
%token<numI> INT_C "integer constant"
%token<numC> CHAR_C "char constant"
%define parse.error verbose
%start input

%%

input:			classdef END
;

classdef:		CLASS IDENT {
	if(context.globalfinding) {context.addClass(GRL::Class(*$2));}
} '{' classcont '}' 
|			NOCLASS '{' classcont '}'
;
classcont:		%empty
|			classcont fundef
|			classcont fielddef
;
fundef:			modifiers typeident IDENT '(' fundefargs ')' {
	if(context.globalfinding) {context.addFunction(GRL::Function(*$3));}
} explicitcodeblock
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

typeident:		IDENT			{if(!context.globalfinding){
	if(context.getIdentifier(*$1,GRL::Identifier::CLASS).type==GRL::Identifier::NOTHING){
		YYERROR;
	}
}}
|			typeident '[' ']'
|			VOID_T
|			BOOL_T
|			FLOAT_T
|			DOUBLE_T
|			BYTE_T
|			CHAR_T
|			SHORT_T
|			INT_T
|			LONG_T
|			UNSIGNED BYTE_T
|			UNSIGNED SHORT_T
|			UNSIGNED INT_T
|			UNSIGNED LONG_T
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
funcall:		IDENT '(' funcallargs ')' {}
;
funcallargs:		noemptyfuncallargs
|			%empty
;
noemptyfuncallargs:	noemptyfuncallargs ',' expression
|			expression
;
%%
