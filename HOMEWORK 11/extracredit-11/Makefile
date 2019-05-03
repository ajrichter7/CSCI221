CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp chrome deme

tsp: tsp.o chromosome.o deme.o cities.o climb_chromosome.o tournament_deme.o
	$(CXX) $(LDFLAGS) -o $@ $^

chrome : chromosome.cc
	$(CXX) $(LDFLAGS) cities.cc chromosome.cc -o chrome

deme : deme.cc
	$(CXX) $(LDFLAGS) deme.cc chromosome.cc cities.cc climb_chromosome.cc -o deme

climb : climb_chromosome.cc
	$(CXX) $(LDFLAGS) cities.cc chromosome.cc climb_chromosome.cc -o climb

tour : tournament_deme.cc
	$(CXX) $(LDFLAGS) tournament_deme.cc deme.cc chromosome.cc cities.cc 			climb_chromosome.cc -o tour

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp chrome climb deme tour
