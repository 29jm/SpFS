CXXFLAGS = -std=c++11 -Wall -isystem "include"
OBJS = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
EXAMPLES = $(patsubst examples/%.cpp, %.cpp, $(wildcard examples/*.cpp))

.PHONY = SpFS all clean

all: SpFS examples

clean:
	rm src/*.o libSpFS.a
	find . -maxdepth 2 -type f -executable | xargs rm

SpFS: $(OBJS)
	$(AR) rvs libSpFS.a $(OBJS)

examples: SpFS $(EXAMPLES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.cpp:
	$(CXX) $(CXXFLAGS) examples/$@ libSpFS.a -o examples/$(patsubst %.cpp,%,$@)
