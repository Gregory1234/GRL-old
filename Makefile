

all: bin/grl
	./bin/grl main.grl

debug: bin/grl
	./bin/grl main.grl -d

bin/grl: int gen $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp)) bin
	c++ -Wall -Wextra -std=c++11 -o bin/grl $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp))


int/%.o: src/%.cpp $(wildcard src/includes/*.h)
	c++ -Wall -Wextra -std=c++11 -I src/includes -c -o $@ $<
int/%.o: gen/%.c $(patsubst src/%.y,gen/%.h,$(wildcard src/*.y)) $(wildcard src/includes/*.h)
	c++ -std=c++11 -I src/includes -c -o $@ $<
gen/%.c: src/%.l
	flex -o $@ $<
gen/%.c gen/%.h: src/%.y
	bison -d -o $(patsubst gen/%.h,gen/%.c,$@) $<

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
