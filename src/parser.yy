%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parse.error verbose
%define api.namespace {GRL}
%define parser_class_name {Parser}

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

%token END 0 "end of file"
%token CLASS "class" NOCLASS "noclass"
%token IDENTIFIER "identifier"
%token VOID_T "void" CHAR_T "char" BOOL_T "bool"
%token BYTE_T "byte" INT8_T "int8" SHORT_T "short" WORD_T "word" INT16_T "int16"
%token INT_T "int" INT32_T "int32" LONG_T "long" INT64_T "int64"
%token FLOAT_T "float" DOUBLE_T "double" QUADRUPLE_T "quadruple"

%locations
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
;

fun_def:	mods type IDENTIFIER '(' ')' ';'
|		mods type IDENTIFIER '(' ')' '{' '}'
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
