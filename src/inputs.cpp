#include <inputs.h>
#include <iostream>

GRL::input::input(int argc,char* argv[]){
	debug=false;
	out="out.o";
	format="nothing";
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
				std::cout << "unknown flag -" << argv[i][1] << std::endl;
				break;
			}
		}else{
			in=argv[i];
		}
	}
}
