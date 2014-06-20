CXX = clang++
CXXFLAGS = -std=c++11
DEPS = Node.o File.o Directory.o FileSystem.o main.o

all: $(DEPS)
	$(CXX) $(CXXFLAGS) $(DEPS) -o fs_test

debug: CXXFLAGS += -g
debug: clean all

clean:
	rm *.o

Node.o: Node.hpp Node.cpp
	$(CXX) $(CXXFLAGS) -c Node.cpp -o Node.o

File.o: File.hpp File.cpp
	$(CXX) $(CXXFLAGS) -c File.cpp -o File.o

Directory.o: Directory.hpp Directory.cpp
	$(CXX) $(CXXFLAGS) -c Directory.cpp -o Directory.o

FileSystem.o: FileSystem.hpp FileSystem.cpp
	$(CXX) $(CXXFLAGS) -c FileSystem.cpp -o FileSystem.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o