#ifndef GRL_STRUCTURE_H
#define GRL_STRUCTURE_H
#include<string>
#include<vector>
#define GRL_STAGE_COMPILING     0
#define GRL_STAGE_GLOBALS       1
namespace GRL{
        struct Class{
                std::string name;

        };
        struct GRLType{
                enum primitives{
                        CHAR,BYTE,SHORT,INT,LONG,VOID
                };
                union{
                        primitives p;
                        Class *c;
                };
                bool isPrimitive;
        };
        struct Function{
                std::string name;
                GRLType ret;
        };
        struct CompilerContext{
                std::vector<Class> classes;
                std::vector<Function> functions;
                short stage = GRL_STAGE_COMPILING;
        };
}

#endif //GRL_STRUCTURE_H
