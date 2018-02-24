.PRECIOUS: int/%.o gen/%.c

all: bin/grl
	./bin/grl main.grl

bin/grl: $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp)) bin
	c++ -o bin/grl $(patsubst src/%.y,int/%.o,$(wildcard src/*.y)) $(patsubst src/%.l,int/%.o,$(wildcard src/*.l)) $(patsubst src/%.cpp,int/%.o,$(wildcard src/*.cpp))


int/%.o: src/%.cpp int
	c++ -c -o $@ $<
int/%.o: gen/%.c int
	c++ -c -o $@ $<
gen/%.c: src/%.l gen
	flex -o $@ $<
gen/%.c: src/%.y gen
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
