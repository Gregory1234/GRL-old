#include<structure.h>


void getDefault(GRL::CompilerContext &c){
	c.functions.push_back(GRL::Function("println",GRL::GRLType::primitives::VOID));
	c.classes.push_back(GRL::Class("String"));
}
