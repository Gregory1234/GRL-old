#ifndef GRL_SCANNER_H
#define GRL_SCANNER_H

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include <parser.hh>
#include <location.hh>

namespace GRL{

class Scanner : public yyFlexLexer{
public:

	Scanner(std::istream *in) : yyFlexLexer(in)
	{
		loc = new GRL::Parser::location_type();
	};

	using FlexLexer::yylex;

	virtual
	int yylex(GRL::Parser::semantic_type* const lval, GRL::Parser::location_type *location);


private:
	GRL::Parser::semantic_type *yylval = nullptr;
	GRL::Parser::location_type *loc = nullptr;
};

}

#endif //GRL_SCANNER_H
