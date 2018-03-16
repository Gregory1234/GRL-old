#ifndef GRL_STRUCTURE_H
#define GRL_STRUCTURE_H
#include<string>
#include<vector>
#define GRL_STAGE_COMPILING     0
#define GRL_STAGE_GLOBALS       1
namespace GRL{
        struct Class{
                std::string name;
                Class(std::string&);
        };
        struct GRLType{
                enum primitives{
                        CHAR,BYTE,SHORT,INT,LONG,BOOL,FLOAT,DOUBLE,VOID,UNDEFINED
                };
                union{
                        primitives p;
                        Class *c;
                };
                bool isPrimitive;
                GRLType(Class&);
                GRLType(primitives);
                GRLType(primitives,bool);
        };
        struct Function{
                std::string name;
                GRLType ret;
                Function(std::string&);
                Function(std::string&,GRLType&);
        };
        enum class IdentifierType{
                FUNCTION,CLASS,NOTHING
        };
        struct CompilerContext{
                std::vector<Class> classes;
                std::vector<Function> functions;
                short stage = GRL_STAGE_COMPILING;
                IdentifierType getIdentifier(std::string&);
        };
}

#endif //GRL_STRUCTURE_H
