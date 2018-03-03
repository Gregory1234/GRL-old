#include<structure.h>
#include<context.h>


void getDefault(GRL::CompilerContext &c){
	c.addFunction(GRL::Function("println"));
	c.addClass(GRL::Class("String"));
}
