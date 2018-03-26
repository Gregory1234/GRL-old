%defines
%code requires{
#include<structure.h>
#include<context.h>
extern GRL::CompilerContext context;
}
%{
#include<string>
#include<iostream>
#include<context.h>
#include<errors.h>
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
	if(context.stage==GRL_STAGE_GLOBALS) {
		context.addClass(GRL::Class(*$2));
	}
} '{' classcont '}'
|			NOCLASS '{' classcont '}'
;
classcont:		%empty
|			classcont fundef
|			classcont fielddef
;
fundef:			modifiers typeident IDENT '(' fundefargs ')' {
	if(context.stage==GRL_STAGE_GLOBALS) {
		context.addFunction(GRL::Function(*$3,*$2));
	}
} explicitcodeblock {$$=new GRL::Function(*$3,*$2);}
;
codeblock:		{++context;} explicitcodeblock {--context;}
|			{++context;} codeline {--context;}
;
explicitcodeblock:	'{' codelines '}'
;
codelines:		codelines codeline
|			%empty
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
		if(context.getIdentifierType(*$1)!=GRL::IdentifierType::CLASS){
			yyerror((std::string("Unknown identifier: ") + *$1).c_str());
		}
	}
	$$=new GRL::GRLType(GRL::GRLType::UNDEFINED);
}
|			typeident '[' ']' {$$=new GRL::GRLType(*$1);}
|			VOID_T {$$=new GRL::GRLType(GRL::GRLType::VOID);}
|			BOOL_T {$$=new GRL::GRLType(GRL::GRLType::BOOL);}
|			FLOAT_T {$$=new GRL::GRLType(GRL::GRLType::FLOAT);}
|			DOUBLE_T {$$=new GRL::GRLType(GRL::GRLType::DOUBLE);}
|			BYTE_T {$$=new GRL::GRLType(GRL::GRLType::BYTE);}
|			CHAR_T {$$=new GRL::GRLType(GRL::GRLType::CHAR);}
|			SHORT_T {$$=new GRL::GRLType(GRL::GRLType::SHORT);}
|			INT_T {$$=new GRL::GRLType(GRL::GRLType::INT);}
|			LONG_T {$$=new GRL::GRLType(GRL::GRLType::LONG);}
|			UNSIGNED BYTE_T {$$=new GRL::GRLType(GRL::GRLType::BYTE,true);}
|			UNSIGNED SHORT_T {$$=new GRL::GRLType(GRL::GRLType::SHORT,true);}
|			UNSIGNED INT_T {$$=new GRL::GRLType(GRL::GRLType::INT,true);}
|			UNSIGNED LONG_T {$$=new GRL::GRLType(GRL::GRLType::LONG,true);}
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
|			typeident IDENT {
	if(context.stage==GRL_STAGE_GLOBALS) {
		context.addVariable(GRL::Variable(*$2,*$1));
	}
} ';'
|			typeident IDENT {
	if(context.stage==GRL_STAGE_GLOBALS) {
		context.addVariable(GRL::Variable(*$2,*$1));
	}
} '=' expression ';'
|			IDENT {
	if(context.stage==GRL_STAGE_COMPILING){
		if(context.getIdentifierType(*$1)!=GRL::IdentifierType::VARIABLE){
			yyerror((std::string("Unknown identifier: ") + *$1).c_str());
		}
	}
} '=' expression ';'
;
expression:		funcall
|			STRING_C
|			CHAR_C
|			INT_C
;
funcall:		IDENT '(' funcallargs ')' {
	if(context.stage==GRL_STAGE_COMPILING){
		if(context.getIdentifierType(*$1)!=GRL::IdentifierType::FUNCTION){
			yyerror((std::string("Unknown identifier: ") + *$1).c_str());
		}
	}
	$$=context.getFunction(*$1);
}
;
funcallargs:		noemptyfuncallargs
|			%empty
;
noemptyfuncallargs:	noemptyfuncallargs ',' expression
|			expression
;
%%
