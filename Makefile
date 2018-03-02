

all: bin/grl
	./bin/grl main.grl

debug: bin/grl
	./bin/grl main.grl -d

bin/grl: int gen $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp)) bin
	c++ -std=c++11 -o bin/grl $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp))


int/%.o: src/%.cpp
	c++ -std=c++11 -I src -c -o $@ $<
int/%.o: gen/%.c
	c++ -std=c++11 -I src -c -o $@ $<
gen/%.c: src/%.l $(patsubst src/%.y,gen/%.h,$(wildcard src/*.y))
	flex -o $@ $<
gen/%.c gen/%.h: src/%.y
	bison -d -o $@ $<

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
