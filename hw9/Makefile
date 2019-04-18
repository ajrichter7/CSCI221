CXX=g++-8
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  cities

cities: cities.cc
	$(CXX) $(LDFLAGS) cities.cc -o cities 

tsp: tsp.cc
	$(CXX) $(LDFLAGS) tsp.cc cities.cc -o tsp

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o