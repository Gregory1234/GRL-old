#include <cctype>
#include <fstream>
#include <cassert>

#include <driver.h>
#include <errors.h>

GRL::Driver::~Driver(){
	delete scanner;
	scanner = nullptr;
	delete parser;
	parser = nullptr;
}

void GRL::Driver::parse(const char* const filename){
	assert(filename!=nullptr);
	std::ifstream in_file(filename);
	if(!in_file.good()){
		 exit(EXIT_FAILURE);
	}
	parse_helper(in_file);
	return;
}

void GRL::Driver::parse(std::istream &stream){
	if(!stream.good()&&stream.eof()){
		 return;
	}
	parse_helper(stream);
	return;
}


void GRL::Driver::parse_helper(std::istream &stream){

	delete scanner;
	try{
		scanner = new GRL::Scanner(&stream);
	}
	catch(std::bad_alloc &ba){
		GRL::inerror(std::string("failed to allocate scanner: (") + ba.what() + ")");
		exit(EXIT_FAILURE);
	}

	delete(parser);
	try{
		parser = new GRL::Parser( (*scanner),(*this));
	}
	catch(std::bad_alloc &ba){
		GRL::inerror(std::string("failed to allocate parser: (") + ba.what() + ")");
		exit(EXIT_FAILURE);
	}
	const int accept(0);
	if(parser->parse() != accept){
	}
	return;
}
