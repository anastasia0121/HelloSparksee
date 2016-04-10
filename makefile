SRC=src/*.cpp
TSTSRC="test/main_test.cpp"
TSTSRC+="src/Wrapper.cpp"
TSTSRC+="src/MyExport.cpp"
TSTSRC+="src/WrapperExportImport.cpp"
TSTSRC+="src/KeyboardLayout.cpp"
HEADER="../sparkseecpp-5.2.2_cpp11/includes/sparksee"
LIB="../sparkseecpp-5.2.2_cpp11/lib/linux64"

all:
	g++ -I$(HEADER) -L$(LIB) $(SRC) -o HelloSparksee -std=c++11 -lsparksee -lpthread

graph:
	dot test.dot -Tps -o hello.ps

debug:
	g++ -I../sparkseecpp-5.2.2_cpp11/includes/sparksee -L../sparkseecpp-5.2.2_cpp11/lib/linux64 $(SRC) -o HelloSparksee -std=c++11 -lsparksee -lpthread -g2

tests:
	g++ -I$(HEADER) -I./src -L$(LIB) $(TSTSRC) -o HelloSparkseeTestik -std=c++11 -lsparksee -lpthread


clean:
	rm -rf *.gdb *.log *.o
