#include <inputs.h>
#include <iostream>
#include <string>
extern int haserrors;
extern void inerror(const char*);
GRL::input::input(int argc,char* argv[]){
	debug=false;
	out="";
	in="";
	format="";
	bool hasdebug = false;
	bool hasout = false;
	bool hasin = false;
	bool hasformat = false;
	for(int i = 1;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'o':
				if(hasout)
					inerror("output was specified twice");
				hasout=true;
				out = argv[++i];
				break;
			case 'f':
				if(hasformat)
					inerror("format was specified twice");
				hasformat=true;
				format = argv[++i];
				break;
			case 'd':
				if(hasdebug)
					inerror("debug was enabled twice");
				hasdebug=true;
				debug = true;
				break;
			default:
				inerror((std::string("unknown flag -") + argv[i][1]).c_str());
				break;
			}
		}else{
			if(hasin)
				inerror("input was specified twice");
			hasin=true;
			in=argv[i];
		}
	}
	if(!hasin)
		inerror("input wan't specified");
}
