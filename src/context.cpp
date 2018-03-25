#include<context.h>

GRL::IdentifierType GRL::CompilerContext::getIdentifierType(const std::string& s){
        if(getFunction(s)!=nullptr)
                return IdentifierType::FUNCTION;
        else if(getClass(s)!=nullptr)
                return IdentifierType::CLASS;
        return IdentifierType::NOTHING;
}
GRL::Function* GRL::CompilerContext::getFunction(const std::string& s){
        for(auto& f: functions){
                if(f.name==s)
                        return &f;
        }
        return nullptr;
}
GRL::Class* GRL::CompilerContext::getClass(const std::string& s){
        for(auto& c: classes){
                if(c.name==s)
                        return &c;
        }
        return nullptr;
}
void GRL::CompilerContext::findGlobals(const std::string& fn){
        //TODO
}
