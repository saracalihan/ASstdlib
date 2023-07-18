FLAGS= -D ASSTD_TODO -D ASSTD_FIXME
TEST_FILES= StringView Vector
all: compile run

compile:
	g++ test.cpp $(FLAGS)
run: 
	./a.out
test:
	echo "Test cases  running"
	g++ tests/LinkedList.cpp -std=gnu++17 -Wno-write-strings
	./a.out
