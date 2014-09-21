override CXXFLAGS = -std=c++11 -Wall
LIBFLAGS = -fPIC
DEPS = Node.o File.o Directory.o FileSystem.o
EXAMPLES = example_write.o example_read.o interpreter.o

all: SpFS examples

debug: CXXFLAGS += -g
debug: clean all

clean:
	rm -f *.o

install:
	cp -f libSpFS.so /usr/lib
	mkdir -p /usr/include/SpFS
	cp -f *.hpp /usr/include/SpFS

uninstall:
	rm /usr/lib/libSpFS.so
	rm -r /usr/include/SpFS

SpFS: $(DEPS)
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -shared $(DEPS) -o libSpFS.so

examples: $(EXAMPLES)
	$(CXX) $(CXXFLAGS) example_write.o -L "." -lSpFS -o example_write
	$(CXX) $(CXXFLAGS) example_read.o -L "." -lSpFS -o example_read
	$(CXX) $(CXXFLAGS) interpreter.o -L "." -lSpFS -o interpreter

Node.o: Node.hpp Node.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c Node.cpp -o Node.o

File.o: File.hpp File.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c File.cpp -o File.o

Directory.o: Directory.hpp Directory.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c Directory.cpp -o Directory.o

FileSystem.o: FileSystem.hpp FileSystem.cpp
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -c FileSystem.cpp -o FileSystem.o

example_write.o: examples/example_write.cpp
	$(CXX) $(CXXFLAGS) -c -I"./" examples/example_write.cpp -o example_write.o

example_read.o: examples/example_read.cpp
	$(CXX) $(CXXFLAGS)  -c -I"./" examples/example_read.cpp -o example_read.o

interpreter.o: examples/interpreter.cpp
	$(CXX) $(CXXFLAGS) -c -I"./" examples/interpreter.cpp -o interpreter.o
