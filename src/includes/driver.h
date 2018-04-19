#ifndef GRL_DRIVER_H
#define GRL_DRIVER_H

#include <string>
#include <cstddef>
#include <istream>

#include <scanner.h>
#include <parser.hh>

namespace GRL{

	class Driver{
	public:
		Driver() = default;
		virtual ~Driver();
		void parse(const char *filename);
		void parse(std::istream &iss);
	private:
		void parse_helper(std::istream &stream);
		GRL::Parser *parser = nullptr;
		GRL::Scanner *scanner = nullptr;
	};
}
#endif //GRL_DRIVER_H
