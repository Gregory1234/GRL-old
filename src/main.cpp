#include <iostream>
#include <cstdlib>
#include <cstring>

#include <driver.h>

int main( const int argc, const char **argv ){
	if( argc == 2 ){
	   	GRL::Driver driver;
		driver.parse( argv[1] );
	}
	else{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS ;
}
