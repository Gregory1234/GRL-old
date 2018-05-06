#include <inputs.h>
#include <errors.h>
#include <iostream>
#include <string>
#include <cstring>

#include <driver.h>

extern int yydebug;

void GRL::input(const int argc, const char* argv[]){
  bool hasinfile=false;
  std::string infile;
  //bool hasoutfile=false;
  //std::string outfile;
  //bool debug=false;
  for(int i = 1;i<argc;i++){
    //const char* v = (i==argc-1||strlen(argv[i])>2?argv[i]+2:argv[i+1]);
    if(argv[i][0]=='-')
      switch(argv[i][1]){

      }
    else{
      if(hasinfile){
        inerror("mutiple input files");
      }
      hasinfile=true;
      infile=argv[i];
    }
  }
  GRL::Driver driver;
  driver.parse(argv[1]);
}
