#ifndef GRL_CONTEXT_H
#define GRL_CONTEXT_H
#include<structure.h>
namespace GRL{
	class CompilerContext{
	public:
		bool globalfinding;
		Class* main;
		Class* cl;
		Function* f;
		std::vector<Identifier> globals;
		std::vector<Identifier> locals;
		
		Identifier& getIdentifier(std::string &name,Identifier::IdentifierType type);
		
		
		CompilerContext(): globalfinding(false){
			
		}
		
		void addClass(Class& f);

		void addClass(Class f);
		
		void addFunction(Function& f);

		void addFunction(Function f);
		
		void scanForGlobals(std::string filename);
		
		
	};
}
#endif //GRL_CONTEXT_H
