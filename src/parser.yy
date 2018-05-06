%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parse.error verbose
%define api.namespace {GRL}
%define parser_class_name {Parser}
%locations

%code requires{
	namespace GRL {
	   	class Driver;
		class Scanner;
	}

	#ifndef YY_NULLPTR
	#define YY_NULLPTR nullptr
	#endif
}

%parse-param {Scanner& scanner}
%parse-param {Driver& driver}

%code{
	#include <iostream>
	#include <cstdlib>
	#include <fstream>
	#include <driver.h>
	#include <errors.h>

	#undef yylex
	#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%right '?' ':'
%left "||"
%left "^^"
%left "&&"
%left "==" "!="
%left '+' '-'
%left '|'
%left '^'
%left '&'
%left '*' '/'
%left "instanceof"
%right '!'
%left '('


%token END 0 "end of file"
%token CLASS "class" NOCLASS "noclass"
%token IDENTIFIER "identifier"
%token VOID_T "void" CHAR_T "char" BOOL_T "bool"
%token BYTE_T "byte" INT8_T "int8" SHORT_T "short" WORD_T "word" INT16_T "int16"
%token INT_T "int" INT32_T "int32" LONG_T "long" INT64_T "int64"
%token FLOAT_T "float" DOUBLE_T "double" QUADRUPLE_T "quadruple"
%token STRING_C "string constant"
%token INT_C "integer constant"
%token DOUBLE_C "double constant"
%token OR "||" AND "&&" XOR "^^" EQUALS "==" NOTEQUALS "!="
%token IF "if" FOR "for" WHILE "while" DO "do" TRY "try" CATCH "catch"
%token INSTANCEOF "instanceof" THROW "throw" CAST "cast"
%start input

%%

input: 		class_def
;

class_def:	"class" IDENTIFIER '{' class_con '}'
|		"noclass" '{' class_con '}'
;

class_con:	class_con fun_def
|		class_con var_def
|		%empty
;

var_def:	mods type IDENTIFIER ';'
|		mods type IDENTIFIER '=' expression ';'
;

fun_def:	mods type IDENTIFIER '(' params ')' ';'
|		mods type IDENTIFIER '(' params ')' compound_statement
;

params:		%empty
|		params_helper
;

params_helper:	type ',' params_helper
|		type IDENTIFIER ',' params_helper
|		type
|		type IDENTIFIER
;

statement:	';'
|		expression_or_var ';'
|		compound_statement
|		"if" '(' expression ')' statement
|		"for" '(' expression_or_var ';' expression ';' expression_or_var ')' statement
|		"for" '(' type IDENTIFIER ':' expression ')' statement
|		"while" '(' expression ')' statement
|		"do" statement "while" '(' expression ')' ';'
|		"try" statement "catch" '(' expression_or_var ')' statement
|		"throw" expression ';'
;

compound_statement:	'{' statement_list '}'
;

statement_list:	statement statement_list
|		%empty
;

expression_or_var:	expression
|		IDENTIFIER '=' expression
|		type IDENTIFIER
|		type IDENTIFIER '=' expression
;

expression:	IDENTIFIER '(' params_call ')'
|		IDENTIFIER
|		STRING_C
|		INT_C
|		DOUBLE_C
|		expression '+' expression
|		expression '-' expression
|		expression '*' expression
|		expression '/' expression
|		"cast" '(' type ')' expression %prec '!'
|		'(' expression ')'
|		expression '&' expression
|		expression '|' expression
|		expression '^' expression
|		'!' expression
|		expression "&&" expression
|		expression "||" expression
|		expression "^^" expression
|		expression "==" expression
|		expression "!=" expression
|		expression '?' expression ':' expression
|		expression "instanceof" type
;

params_call:	%empty
|		params_helper_call
;

params_helper_call:	expression ',' params_helper_call
|		expression
;

mods:		%empty
;

type:		VOID_T
|		BOOL_T
|		CHAR_T
|		BYTE_T
|		INT8_T
|		SHORT_T
|		WORD_T
|		INT16_T
|		INT_T
|		DOUBLE_T WORD_T
|		INT32_T
|		LONG_T
|		QUADRUPLE_T WORD_T
|		INT64_T
|		FLOAT_T
|		DOUBLE_T
|		IDENTIFIER
;

%%
void GRL::Parser::error(const location_type &l, const std::string &m){
	GRL::prserror(l, m);
}
