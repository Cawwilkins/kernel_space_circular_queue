CXX = gcc
CXXFLAGS = -Wall

build: main_program

main_program: main_program.o
	$(CXX) $(CXXFLAGS) main_program.o -o main_program

main_program.o: main_program.c 421queue.h
	$(CXX) $(CXXFLAGS) -c main_program.c

clean:
	@rm -f *~ *.o *.save main_program

run:
	./main_program
