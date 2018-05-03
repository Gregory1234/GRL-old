#ifndef GRL_SCANNER_H
#define GRL_SCANNER_H

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include <parser.hh>
#include <location.hh>
#undef  YY_DECL
#define YY_DECL int GRL::Scanner::yylex( GRL::Parser::semantic_type * const yyllval, GRL::Parser::location_type *yylloc )

namespace GRL{

class Scanner : public yyFlexLexer{
public:

	Scanner(std::istream *in) : yyFlexLexer(in)
	{
	}

	using FlexLexer::yylex;

	virtual
	int yylex(GRL::Parser::semantic_type* const yylval, GRL::Parser::location_type *yylloc);
};

}

#endif //GRL_SCANNER_H
