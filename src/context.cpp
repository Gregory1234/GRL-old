#include<context.h>
GRL::Identifier& GRL::CompilerContext::getIdentifier(std::string &name,GRL::Identifier::IdentifierType type){
	for(auto i = locals.begin(); i != locals.end(); ++i) {
		if(i->name==name&&i->type==type)
			return *i;
	}
	for(auto i = globals.begin(); i != globals.end(); ++i) {
		if(i->name==name&&i->type==type)
			return *i;
	}
	yyerror((name+" is an unknown identifier!").c_str());
	return notFound;
}

void GRL::CompilerContext::addClass(GRL::Class& f){
	globals.push_back(Identifier(f));
}

void GRL::CompilerContext::addClass(GRL::Class f){
	globals.push_back(Identifier(f));
}

void GRL::CompilerContext::addFunction(GRL::Function& f){
	globals.push_back(Identifier(f));
}

void GRL::CompilerContext::addFunction(GRL::Function f){
	globals.push_back(Identifier(f));
}

void GRL::CompilerContext::scanForGlobals(std::string filename){
	std::ifstream mainfs;

	scanFile(filename);
	mainfs.open(filename.c_str());
	char c;
	int l = 0;
	std::string line;
	while(c!='{'){
		c=mainfs.get();
		if(c==' '||c=='\n'||c=='\t'){
			if(c=='n')
				l++;
			continue;
		}
		if(c==';'){
			scanFile(line);
			if(haserrors)
				return;
			line="";
			continue;
		}
		if(c=='{'){
			if(line=="noclass")
				continue;
			std::string f = filename.substr(0,filename.length()-4);
			f=f.substr(f.rfind("/")+1,f.size());
			if(line!=f){
				std::cout << "\033[1;31mpre-parsing error:\033[0m in " << filename << " line " << l << std::endl << "wrong class name error, expected " << f << std::endl;
				haserrors=PRE_PARSING_ERROR;
			}
		}
		line+=c;
		if(line=="class"){
			line="";
		}
		if(line=="import"){
			line="";
		}
	}
	mainfs.close();
}
