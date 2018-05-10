#ifndef GRL_CONTEXT_H
#define GRL_CONTEXT_H
#include <vector>
#include <string>
#include <structure.h>
namespace GRL{
	enum class IdentifierType{
		CLASS,FUNCTION,VARIABLE
	};
	class ContextLayer{
		std::vector<Structure::Variable> vars;
		std::vector<Structure::Function> funs;
		std::vector<Structure::Class> classes;
	public:
		IdentifierType getType(std::string);
		Structure::Variable getVariable(std::string);
		Structure::Function getFunction(std::string);
		Structure::Class getClass(std::string);
		void addVariable(Structure::Variable);
		void addFunction(Structure::Function);
		void addClass(Structure::Class);
	};
	class Context{
	public:
		std::vector<ContextLayer> layers;
		void operator++();
		void operator--();
		IdentifierType getType(std::string);
		Structure::Variable getVariable(std::string);
		Structure::Function getFunction(std::string);
		Structure::Class getClass(std::string);
		void addVariable(Structure::Variable);
		void addFunction(Structure::Function);
		void addClass(Structure::Class);
	};

}
#endif //GRL_CONTEXT_H
