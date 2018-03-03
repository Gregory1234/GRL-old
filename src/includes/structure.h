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
	
	
	
	
}




#endif //GRL_STRUCTURE_H
