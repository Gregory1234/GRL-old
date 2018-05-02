%{
#include <string>

#include <errors.h>
#include <scanner.h>
#undef  YY_DECL
#define YY_DECL int GRL::Scanner::yylex( GRL::Parser::semantic_type * const lval, GRL::Parser::location_type *location )

using token = GRL::Parser::token;
#define yyterminate() return token::END
#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

//yylval->build<std::string>(yytext);
%}

%option debug
%option nodefault
%option yyclass="GRL::Scanner"
%option noyywrap
%option c++

%%
%{
            yylval = lval;
%}

"class"				{return token::CLASS;}
"noclass"			{return token::NOCLASS;}

"void"  			{return token::VOID_T;}
"bool"  			{return token::BOOL_T;}
"char"  			{return token::CHAR_T;}
"byte"  			{return token::BYTE_T;}
"int8"  			{return token::INT8_T;}
"short"  			{return token::SHORT_T;}
"word"  			{return token::WORD_T;}
"int16"  			{return token::INT16_T;}
"int"  			        {return token::INT_T;}
"int32"	                        {return token::INT32_T;}
"long"  			{return token::LONG_T;}
"int64"  			{return token::INT64_T;}
"float"  			{return token::FLOAT_T;}
"double"  			{return token::DOUBLE_T;}
"quadruple"  			{return token::QUADRUPLE_T;}

[a-zA-Z_][a-zA-Z1-9_]*		{return token::IDENTIFIER;}

[{}()\[\]<>]			{return yytext[0];}

[;=+\-*/]			{return yytext[0];}

[ \t]				{}
\n				{loc->lines();}
.				{GRL::lexerror(*loc,"unexpected character!");}
%%
