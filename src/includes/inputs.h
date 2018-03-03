#ifndef GRL_INPUT_H
#define GRL_INPUT_H
#include<string>
namespace GRL{
	struct input{
		std::string in;
		std::string out;
		bool debug;
		std::string format;
		input(int argc,char* argv[]);
	};
}

#endif //GRL_INPUT_H
