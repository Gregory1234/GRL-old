#ifndef GRL_STRUCTURE_H
#define GRL_STRUCTURE_H
#include<string>
#include<vector>
namespace GRL{
        struct Class{
                std::string name;
                Class(const std::string&);
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
                bool nosign;
                GRLType(Class*);
                GRLType(primitives);
                GRLType(primitives,bool);
        };
        struct Function{
                std::string name;
                GRLType ret;
                Function(const std::string&);
                Function(const std::string&,const GRLType&);
        };
        struct Variable{
                std::string name;
                GRLType ret;
                Variable(const std::string&,const GRLType&);
        };
        enum class IdentifierType{
                FUNCTION,CLASS,VARIABLE,NOTHING
        };
}

#endif //GRL_STRUCTURE_H
