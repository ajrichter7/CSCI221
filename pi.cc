#include <iostream>
#include <cmath>
//g++ -O3 -Wall -Wextra -pedantic pi.cc -o pi

/*
Function checks to see if a point has a hypotenuse greater than the radius.
If the hypotenuse is greater than the radius, then the point referenced is under
the arch, and belongs to the number needed to be divided by the total number
of point. Returns a double that serves as the estimate for pi.
*/

double gridpi(unsigned Numberofgridpoints){
  int countinsidecircle = 0;
  double height;
  double width;
  for (height= 0.0; height <= Numberofgridpoints; ++height){
    for (width= 0.0; width <= Numberofgridpoints; ++width){
      double hypotenuse;
      hypotenuse = std::hypot(width, height);
      if (hypotenuse < Numberofgridpoints)
        ++ countinsidecircle;
    }
  }
  double pi;
  double totalnumberofpoints = Numberofgridpoints * Numberofgridpoints;
  pi = (countinsidecircle / (totalnumberofpoints)) * 4;
  return pi;
}

int main(){
  double estimate_for_pi;
  estimate_for_pi = gridpi(10);
  std::cout << estimate_for_pi << "\n";
}
