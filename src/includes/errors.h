#ifndef GRL_ERROR_H
#define GRL_ERROR_H
#include <string>
#include <parser.hh>
namespace GRL{
	void error(const std::string&, const std::string&);
	void error(const Parser::location_type&, const std::string&, const std::string&);
	void lexerror(const Parser::location_type&, const std::string&);
	void prserror(const Parser::location_type&, const std::string&);
	void pprserror(const std::string&);
	void inerror(const std::string&);
}

#endif //GRL_ERROR_H
