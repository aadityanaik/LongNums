CPPFLAGS=-g -std=c++11
LDFLAGS=-g

.PHONY: all obj bin clean

all: bin/examples

bin/examples: bin src/examples.cpp obj/longnums.o
	g++ $(LDFLAGS) -o bin/examples src/examples.cpp obj/longnums.o

bin/tests: bin tests/basic.cpp obj/test_util.o obj/longnums.o
	g++ $(LDFLAGS) -o bin/tests tests/basic.cpp obj/test_util.o obj/longnums.o

obj/longnums.o: obj src/longnums.cpp src/longnums.hpp
	g++ $(CPPFLAGS) -o obj/longnums.o -c src/longnums.cpp -O3

obj/test_util.o: obj tests/test_util.cpp tests/test_util.hpp
	g++ $(CPPFLAGS) -o obj/test_util.o -c tests/test_util.cpp -O3

test: bin/tests
	./bin/tests

obj:
	mkdir -p obj/

bin:
	mkdir -p bin/

clean:
	rm -rf obj/ bin/
