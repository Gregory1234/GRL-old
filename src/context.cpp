#include<context.h>
#include<errors.h>
#include<iostream>
#include<fstream>
#include<stdio.h>

extern int yyparse();
extern FILE* yyin;
extern std::string currentfn;
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
				std::cout << "\033[1;31mpre-parsing error:\033[0m in " << fn << " line " << l << std::endl << "wrong class name error, expected " << f << std::endl;
				haserrors=PRE_PARSING_ERROR;
			}
		}
		line+=c;
		if(line=="class"){
			line="";
		}
	}
	mainfs.close();
}
