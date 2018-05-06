%{
#include <string>

#include <errors.h>
#include <scanner.h>

using token = GRL::Parser::token;
#define yyterminate() return token::END
#define YY_NO_UNISTD_H

//yylval->build<std::string>(yytext);
%}

%option debug
%option nodefault
%option yyclass="GRL::Scanner"
%option noyywrap
%option c++

%%
%{
#undef YY_USER_ACTION
#define YY_USER_ACTION yylloc->step();yylloc->columns(yyleng);
%}

"class"				{return token::CLASS;}
"noclass"			{return token::NOCLASS;}

"||"				{return token::OR;}
"&&"				{return token::AND;}
"^^"				{return token::XOR;}
"=="				{return token::EQUALS;}
"!="				{return token::NOTEQUALS;}

"if"				{return token::IF;}
"for"				{return token::FOR;}
"while"				{return token::WHILE;}
"do"				{return token::DO;}
"instanceof"			{return token::INSTANCEOF;}
"try"				{return token::TRY;}
"catch"				{return token::CATCH;}
"throw"				{return token::THROW;}

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

\".*\"  	               	{return token::STRING_C;}
-?(?:[1-9][0-9]*|0)  	               	{return token::INT_C;}
(?:-?(?:[1-9][0-9]*|0))?\.[0-9]*  	{return token::DOUBLE_C;}

[a-zA-Z_][a-zA-Z1-9_]*		{return token::IDENTIFIER;}

[{}()\[\]<>]			{return yytext[0];}

[;=+\-*/,|&^!?:]		{return yytext[0];}

[ \t]				{yylloc->step();}
\n				{yylloc->lines();}
.				{GRL::lexerror(*yylloc,std::string("unexpected character: ")+yytext[0]);}
%%
