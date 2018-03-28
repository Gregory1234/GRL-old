#ifndef GRL_CONTEXT_H
#define GRL_CONTEXT_H
#include <structure.h>
#include <string.h>
#define GRL_STAGE_COMPILING     0
#define GRL_STAGE_GLOBALS       1
namespace GRL{
        class ContextLayer{
                std::vector<Class> classes;
                std::vector<Function> functions;
                std::vector<Variable> variables;
        public:
                IdentifierType getIdentifierType(const std::string&);
                Function* getFunction(const std::string&);
                Class* getClass(const std::string&);
                Variable* getVariable(const std::string&);
                void addFunction(const Function&);
                void addClass(const Class&);
                void addVariable(const Variable&);
        };
        class CompilerContext{
                std::vector<ContextLayer> layers{ContextLayer()};
        public:
                short stage = GRL_STAGE_COMPILING;
                IdentifierType getIdentifierType(const std::string&);
                Function* getFunction(const std::string&);
                Class* getClass(const std::string&);
                Variable* getVariable(const std::string&);
                void addFunction(const Function&);
                void addClass(const Class&);
                void addVariable(const Variable&);
        	void findGlobals(const std::string&);
                void operator++();
                void operator--();

        };
}
extern GRL::CompilerContext context;
#endif //GRL_CONTEXT_H
