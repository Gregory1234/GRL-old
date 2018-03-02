#ifndef GRL_STRUCTURE_H
#define GRL_STRUCTURE_H
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<stdio.h>
#define PRE_PARSING_ERROR 1
#define GLOBAL_FINDING_PARSER_ERROR 2
#define PARSING_ERROR 3
#define LEXER_ERROR 4
#define INPUT_ERROR 5
extern void scanFile(std::string filename);
void yyerror(const char*);
extern int haserrors;
namespace GRL{
	
	
	
	class StructureObject{
	public:
		std::string name;
	};
	class Function;
	class Field;
	
	class Class : public StructureObject{
	public:
	
		std::vector<Function> functions;
		std::vector<Field>    fields;
		Class(std::string name){
			this->name=name;
		}
	};
	
	class GRLType{
	public:
		union{
			Class* c;
			std::string* primitive;
		};
	};
	
	class Function : public StructureObject{
	public:
		GRLType ret;
		std::vector<Field> args;
		Class* cl;
		Function(std::string name){
			this->name=name;
		}
	};
	
	class Field : public StructureObject{
	public:
		GRLType t;
		Field(std::string name){
			this->name=name;
		}
		
	};
	
	class Identifier{
	public:
		std::string name;
		StructureObject* owner;
		enum IdentifierType{FUNCTION,FIELD,CLASS,NOTHING} type;
		Identifier(Function& f) : name(f.name), owner(&f), type(FUNCTION){
			
		}
		Identifier(Class& c) : name(c.name), owner(&c), type(CLASS){
			
		}
		Identifier() : name(""), owner(nullptr), type(NOTHING){
			
		}
	};
	extern Identifier notFound;
	
	
	class CompilerContext{
	public:
		bool globalfinding;
		Class* main;
		Class* cl;
		Function* f;
		std::vector<Identifier> globals;
		std::vector<Identifier> locals;
		
		Identifier& getIdentifier(std::string &name,Identifier::IdentifierType type){
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
		
		
		CompilerContext(): globalfinding(false){
			
		}
		
		void addClass(Class& f){
			globals.push_back(Identifier(f));
		}

		void addClass(Class f){
			globals.push_back(Identifier(f));
		}
		
		void addFunction(Function& f){
			globals.push_back(Identifier(f));
		}

		void addFunction(Function f){
			globals.push_back(Identifier(f));
		}
		
		void scanForGlobals(std::string filename){
			std::ifstream mainfs;

			scanFile(filename);
			mainfs.open(filename.c_str());
			char c;
			int l = 0;
			std::string line;
			bool islast = false;
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
					if(line!=filename.substr(0,filename.length()-4)){
						std::cout << "\033[1;31mpre-parsing error:\033[0m in " << filename << " line " << l << std::endl << "wrong class name error, expected " << filename.substr(0,filename.length()-4) << std::endl;
						haserrors=PRE_PARSING_ERROR;
					}
				}
				line+=c;
				if(line=="class"){
					islast=true;
					line="";
				}
				if(line=="import"){
					line="";
				}
			}
			mainfs.close();
		}
		
		
	};
	
}




#endif //GRL_STRUCTURE_H
