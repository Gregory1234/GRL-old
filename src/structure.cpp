#include<structure.h>
GRL::Class::Class(const std::string& name): name(name){

}
GRL::GRLType::GRLType(GRL::GRLType::primitives p): p(p), isPrimitive(true){

}
GRL::GRLType::GRLType(GRL::GRLType::primitives p,bool nosign): p(p), isPrimitive(true), nosign(nosign){

}
GRL::GRLType::GRLType(GRL::Class* c): c(c), isPrimitive(false){

}
GRL::Function::Function(const std::string& name): name(name), ret(GRL::GRLType::primitives::VOID){

}
GRL::Function::Function(const std::string& name,const GRLType& ret): name(name), ret(ret){

}
