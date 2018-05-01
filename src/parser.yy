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
%token VOID_T "void" INT_T "int"

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
|		INT_T
;

%%
void GRL::Parser::error(const location_type &l, const std::string &m){
	GRL::prserror(l, m);
}
