%defines
%{
#include<string>
void yyerror(const char*);
int yylex();
%}
%union{
	char* str;
}

%token CLASS "class" NOCLASS "noclass"
%token END 0 "end of file"
%token VOID_T "void" BYTE_T "byte" CHAR_T "char" SHORT_T "short" INT_T "int" LONG_T "long" UNSIGNED "unsigned"
%token BOOL_T "bool" FLOAT_T "float" DOUBLE_T "double"
%token PUBLIC_MOD "public" PRIVATE_MOD "private" STATIC_MOD "static"
%token STRING_C "string constant"
%token<str> IDENT "identifier"

%define parse.error verbose
%start input

%%

input:			classdef
;

classdef:		CLASS IDENT '{' classcont '}'
|			NOCLASS '{' classcont '}'
;
classcont:		%empty
|			classcont fundef
|			classcont fielddef
|			classcont classdef
;
fundef:			typeident IDENT '(' fundefargs ')' '{' '}'
;
fundefargs:		%empty
|			fundefargsnotempty
;
fundefargsnotempty:	fundefarg
|			fundefargsnotempty ',' fundefarg
;
fundefarg:		typeident IDENT
;
fielddef:		typeident IDENT ';'
;

typeident:		IDENT
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
%%
