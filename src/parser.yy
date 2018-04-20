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
%token CLASS "class"
%token IDENTIFIER "identifier"

%locations
%start input

%%

input: 		class_def
|		%empty
;

class_def:	"class" IDENTIFIER '{' '}'
;

%%
void GRL::Parser::error(const location_type &l, const std::string &m){
	GRL::prserror(l, m);
}
