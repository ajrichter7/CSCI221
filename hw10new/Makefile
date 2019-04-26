CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp chrome deme

tsp: tsp.o chromosome.o deme.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

chrome : chromosome.cc
	$(CXX) $(LDFLAGS) cities.cc chromosome.cc -o chrome

deme : deme.cc
	$(CXX) $(LDFLAGS) deme.cc chromosome.cc cities.cc -o deme

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp chrome
