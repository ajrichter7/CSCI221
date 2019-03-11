#include <iostream>
#include <cmath>
//g++ -O3 -Wall -Wextra -pedantic --std=c++17  pi2.cc -o pi2

/*
Function checks to see if a point has a hypotenuse greater than the radius.
If the hypotenuse is greater than the radius, then the point referenced is under
the arch, and belongs to the number needed to be divided by the total number
of point. Returns a double that serves as the estimate for pi.

Function runs at compile time. 
*/

constexpr double gridpi2(unsigned Numberofgridpoints){
  int countinsidecircle = 0;
  double hypotenuse = 0;
  for (unsigned int width = 0; width <= Numberofgridpoints; ++width){
    for (unsigned int height = 0; height <= Numberofgridpoints; ++height){
      hypotenuse = std::hypot(width, height);
      if (hypotenuse < Numberofgridpoints){
        ++ countinsidecircle;
      }
    }
  }
  double pi = 0;
  double totalnumberofpoints = Numberofgridpoints * Numberofgridpoints;
  pi = (countinsidecircle / (totalnumberofpoints)) * 4;
  return pi;
}

int main(){
  double estimate_for_pi;
  estimate_for_pi = gridpi2(1000);
  std::cout << estimate_for_pi << "\n";
}
