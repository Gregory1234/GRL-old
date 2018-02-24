#include<iostream>
#include<stdio.h>
#include<fstream>
extern FILE* yyin;
extern int yyparse();
extern int yylineno;
using namespace std;

int main(int argc,char* argv[]){
	const char* fn;
	const char* outfn;
	
	yyin=fopen(argv[1],"r");
	//cout << ifstream(argv[1]).rdbuf() << endl;
	yyparse();
}

void yyerror(const char* msg){
	cout << "Error at line " << yylineno << endl << msg << endl;
}
