CXXFLAGS+=-std=c++17 -Wall -O3
CXX=g++

all: out/main.o

run: out/main.o
	$<

out/main.o: src/main.cpp src/lexical_analyzer.cpp src/parse_exception.cpp src/parser.cpp src/tree.cpp src/parser_tester.cpp
	mkdir -p out
	$(CXX) $^ $(CXXFLAGS) -o $@ -lgvc -lcgraph

clean:
	rm -rf out
