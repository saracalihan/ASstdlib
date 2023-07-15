all: compile run
compile:
	g++ test.cpp
run: 
	./a.out
test:
	echo "Test cases  running"
	g++ tests/StringView.cpp -std=gnu++17 -Wno-write-strings
	./a.out
