#ifndef GRL_STRUCTURE_H
#define GRL_STRUCTURE_H
#include<string>
#include<vector>

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
                        Class c;
                };
                bool isPrimitive;
        };
        struct Function{
                std::string name;
                GRLType ret;
        };
}

#endif //GRL_STRUCTURE_H
