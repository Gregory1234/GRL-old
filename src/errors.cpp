#include <errors.h>
#include <iostream>
#include <sstream>
namespace GRL{
	std::string formatLocation(const Parser::location_type& l){
		std::ostringstream s;
		s<<l;
		std::string str = s.str();
		std::replace(str.begin(),str.end(),'.',':');
		return str;
	}
	void error(const std::string& t, const std::string& m){
		std::cout << "\033[1;31m" << t << " error:\033[0m " << std::endl << m << std::endl;
	}
	void error(const Parser::location_type& l, const std::string& t, const std::string& m){
		std::cout << "\033[1;31m" << t << " error:\033[0m at " << formatLocation(l) << std::endl << m << std::endl;
	}
	void lexerror(const Parser::location_type& l, const std::string& m){
		error(l, "lexing", m);
	}
	void prserror(const Parser::location_type& l, const std::string& m){
		error(l, "parsing", m);
	}
	void pprserror(const std::string& m){
		error("pre-parsing", m);
	}
	void inerror(const std::string& m){
		error("input", m);
	}
}
