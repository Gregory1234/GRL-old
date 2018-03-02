#include <inputs.h>
#include <iostream>
#include <structure.h>
extern int haserrors;

GRL::input::input(int argc,char* argv[]){
	debug=false;
	out="";
	format="";
	for(int i = 1;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'o':
				out = argv[++i];
				break;
			case 'f':
				format = argv[++i];
				break;
			case 'd':
				debug = true;
				break;
			default:
				haserrors = INPUT_ERROR;
				std::cout << "unknown flag -" << argv[i][1] << std::endl;
				break;
			}
		}else{
			in=argv[i];
		}
	}
}
