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
		std::string name;
		GRLType* arrayelement;
		enum typeType{CLASS,PRIMITIVE,ARRAY} type;
		GRLType() = default;
		GRLType(std::string name): name(name){

		}
		GRLType(GRLType* arrayelement): arrayelement(arrayelement){

		}
	};

	class Function : public StructureObject{
	public:
		GRLType ret;
		Class* cl;
		std::vector<Field> args;
		Function() = default;
		Function(std::string name,GRLType ret) : ret(ret), cl(nullptr){
			this->name=name;
		}
		Function(std::string name,GRLType ret, Class* cl) : ret(ret), cl(cl){
			this->name=name;
		}
		Function(std::string name,GRLType ret, std::vector<Field> args) : ret(ret), cl(nullptr), args(args){
			this->name=name;
		}
		Function(std::string name,GRLType ret, Class* cl, std::vector<Field> args) : ret(ret), cl(cl), args(args){
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
