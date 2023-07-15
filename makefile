FLAGS= -D ASSTD_TODO -D ASSTD_FIXME

test: compile run
compile:
	g++ test.cpp $(FLAGS)
run: 
	./a.out