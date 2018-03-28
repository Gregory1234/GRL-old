#include <structure.h>
#include <context.h>


void getDefault(GRL::CompilerContext &c){
	c.addFunction(GRL::Function("println",GRL::GRLType::primitives::VOID));
	c.addClass(GRL::Class("String"));
}
