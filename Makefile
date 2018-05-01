all: bin/grl
	./bin/grl main.grl

debug: bin/grl
	./bin/grl main.grl -d

bin/grl: int gen $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.yy,int/%.o,$(wildcard src/*.yy)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.ll,int/%.o,$(wildcard src/*.ll)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp)) bin
	g++ -Wall -Wextra -std=c++11 -o bin/grl $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.yy,int/%.o,$(wildcard src/*.yy)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.ll,int/%.o,$(wildcard src/*.ll)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp))


int/%.o: src/%.cpp $(wildcard src/includes/*.h)
	g++ -Wall -Wextra -std=c++11 -I src/includes -I gen -c -o $@ $<
int/%.o: gen/%.c $(patsubst src/%.y,gen/%.h,$(wildcard src/*.y)) $(wildcard src/includes/*.h)
	g++ -std=c++11 -I src/includes -I gen -c -o $@ $<
int/%.o: gen/%.cc $(patsubst src/%.yy,gen/%.hh,$(wildcard src/*.yy)) $(wildcard src/includes/*.h)
	g++ -std=c++11 -I src/includes -I gen -c -o $@ $<
gen/%.c: src/%.l
	flex -o $@ $<
gen/%.c gen/%.h: src/%.y
	bison -d -o $(patsubst gen/%.h,gen/%.c,$@) $<
gen/%.cc: src/%.ll
	flex -o $@ $<
gen/%.cc gen/%.hh: src/%.yy
	bison -d -o $(patsubst gen/%.hh,gen/%.cc,$@) $<

bin:
	mkdir bin
int:
	mkdir int
gen:
	mkdir gen

clear:
	rm -rf bin
	rm -rf int
	rm -rf gen
