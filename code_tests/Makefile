CXX = gcc
CXXFLAGS = -Wall

build_poc: main_program.c 421queue.h
	$(CXX) $(CXXFLAGS) main_program.c -o main_program

build_test: test_program.c 421queue.h
	$(CXX) $(CXXFLAGS) test_program.c -o test_program

clean:
	@rm -f *~ *.o *.save main_program

run:
	./main_program

run_t:
	./test_program


