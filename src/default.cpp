#include<structure.h>


void getDefault(GRL::CompilerContext &c){
	c.functions.push_back(GRL::Function("println",GRL::GRLType(std::string("void"))));
	c.classes.push_back(GRL::Class("String"));
}
