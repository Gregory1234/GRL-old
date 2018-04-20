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

[a-zA-Z_][a-zA-Z1-9_]*		{return token::IDENTIFIER;}

[{}()\[\]<>]			{return yytext[0];}

[ \t]				{}
\n				{loc->lines();}
.				{GRL::lexerror(*loc,"unexpected character!");}
%%
