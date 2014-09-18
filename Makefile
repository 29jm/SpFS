CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBFLAGS = -fPIC
DEPS = Node.o File.o Directory.o FileSystem.o
EXAMPLES = example_write.o example_read.o

all: SpFS examples

debug: CXXFLAGS += -g
debug: clean all

clean:
	rm *.o

SpFS: $(DEPS)
	$(CXX) $(CXXFLAGS) $(LIBFLAGS)-shared $(DEPS) -o libSpFS.so	

examples: $(EXAMPLES)
	$(CXX) $(CXXFLAGS) example_write.o -L "." -lSpFS -o example_write
	$(CXX) $(CXXFLAGS) example_read.o -L "." -lSpFS -o example_read

Node.o: Node.hpp Node.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c Node.cpp -o Node.o

File.o: File.hpp File.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c File.cpp -o File.o

Directory.o: Directory.hpp Directory.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c Directory.cpp -o Directory.o

FileSystem.o: FileSystem.hpp FileSystem.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c FileSystem.cpp -o FileSystem.o

example_write.o: examples/example_write.cpp
	$(CXX) $(CXXFLAGS) -I"./" -c examples/example_write.cpp -o example_write.o

example_read.o: examples/example_read.cpp
	$(CXX) $(CXXFLAGS) -I"./" -c examples/example_read.cpp -o example_read.o
