#include<context.h>
#include<errors.h>
#include<iostream>
#include<fstream>
#include<stdio.h>

extern int yyparse();
extern FILE* yyin;
extern std::string currentfn;
GRL::IdentifierType GRL::ContextLayer::getIdentifierType(const std::string& s){
        if(getVariable(s)!=nullptr)
                return IdentifierType::VARIABLE;
        else if(getFunction(s)!=nullptr)
                return IdentifierType::FUNCTION;
        else if(getClass(s)!=nullptr)
                return IdentifierType::CLASS;
        return IdentifierType::NOTHING;
}
GRL::Function* GRL::ContextLayer::getFunction(const std::string& s){
        for(auto& f: functions){
                if(f.name==s)
                        return &f;
        }
        return nullptr;
}
GRL::Class* GRL::ContextLayer::getClass(const std::string& s){
        for(auto& c: classes){
                if(c.name==s)
                        return &c;
        }
        return nullptr;
}
GRL::Variable* GRL::ContextLayer::getVariable(const std::string& s){
        for(auto& v: variables){
                if(v.name==s)
                        return &v;
        }
        return nullptr;
}
void GRL::ContextLayer::addFunction(const GRL::Function& f){
        if(getFunction(f.name)==nullptr)
                functions.push_back(f);
        else
                yyerror((std::string("ambiguous function: ")+f.name).c_str());
}
void GRL::ContextLayer::addClass(const GRL::Class& c){
        if(getClass(c.name)==nullptr)
                classes.push_back(c);
        else
                yyerror((std::string("ambiguous class: ")+c.name).c_str());
}
void GRL::ContextLayer::addVariable(const GRL::Variable& v){
        if(getVariable(v.name)==nullptr)
                variables.push_back(v);
        else
                yyerror((std::string("ambiguous variable: ")+v.name).c_str());
}


GRL::IdentifierType GRL::CompilerContext::getIdentifierType(const std::string& s){
        for(auto& l: layers){
                auto r = l.getIdentifierType(s);
                if(r!=IdentifierType::NOTHING)
                        return r;
        }
        return IdentifierType::NOTHING;
}
GRL::Function* GRL::CompilerContext::getFunction(const std::string& s){
        for(auto& l: layers){
                auto r = l.getFunction(s);
                if(r!=nullptr)
                        return r;
        }
        return nullptr;
}
GRL::Class* GRL::CompilerContext::getClass(const std::string& s){
        for(auto& l: layers){
                auto r = l.getClass(s);
                if(r!=nullptr)
                        return r;
        }
        return nullptr;
}
GRL::Variable* GRL::CompilerContext::getVariable(const std::string& s){
        for(auto& l: layers){
                auto r = l.getVariable(s);
                if(r!=nullptr)
                        return r;
        }
        return nullptr;
}
void GRL::CompilerContext::addFunction(const GRL::Function& f){
        layers.back().addFunction(f);
}
void GRL::CompilerContext::addClass(const GRL::Class& c){
        layers.back().addClass(c);
}
void GRL::CompilerContext::addVariable(const GRL::Variable& v){
        layers.back().addVariable(v);
}
void GRL::CompilerContext::operator++(){
        layers.emplace_back();
}
void GRL::CompilerContext::operator--(){
        layers.pop_back();
}
void GRL::CompilerContext::findGlobals(const std::string& fn){
        std::ifstream mainfs;
        //
        currentfn=fn;
	stage=GRL_STAGE_GLOBALS;
	yyin=fopen(fn.c_str(),"r");
	yyparse();
	stage=GRL_STAGE_COMPILING;
        //
	mainfs.open(fn.c_str());
	char c;
	int l = 0;
	std::string line;
	while(c!='{'){
		c=mainfs.get();
		if(c==' '||c=='\n'||c=='\t'){
			if(c=='\n')
				l++;
			continue;
		}
		if(c=='{'){
			if(line=="noclass")
				continue;
			std::string f = fn.substr(0,fn.length()-4);
			f=f.substr(f.rfind("/")+1,f.size());
			if(line!=f){
                                othererror("pre-parsing",(std::string("wrong class name error, expected ") + f).c_str(), PRE_PARSING_ERROR);
			}
		}
		line+=c;
		if(line=="class"){
			line="";
		}
	}
	mainfs.close();
}
