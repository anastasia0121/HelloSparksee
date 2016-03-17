SRC=src/*.cpp

all:
	g++ -I../sparkseecpp-5.2.2_cpp11/includes/sparksee -L../sparkseecpp-5.2.2_cpp11/lib/linux64 $(SRC) -o HelloSparksee -std=c++11 -lsparksee -lpthread

	#dot test.dot -Tps -o hello.ps

clean:
	rm -rf *.gdb *.log *.o
