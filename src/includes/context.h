#ifndef GRL_CONTEXT_H
#define GRL_CONTEXT_H
#include<structure.h>
#include<string.h>
#define GRL_STAGE_COMPILING     0
#define GRL_STAGE_GLOBALS       1
namespace GRL{
        class CompilerContext{
                std::vector<Class> classes;
                std::vector<Function> functions;
        public:
                short stage = GRL_STAGE_COMPILING;
                IdentifierType getIdentifierType(const std::string&);
                Function* getFunction(const std::string&);
                Class* getClass(const std::string&);
                void addFunction(const Function&);
                void addClass(const Class&);
        	void findGlobals(const std::string&);
        };
}
#endif //GRL_CONTEXT_H
