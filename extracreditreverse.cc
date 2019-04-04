#include <iostream>
#include <cassert>
#include <list>
#include "reversed.hh"

using rlst = std::list<int>;

//////////////////////////////////////////////////////////////////////////////
int main()
{
  linkedlist nlst;
  nlst.push(20);
  nlst.push(12);
  nlst.push(4);
  nlst.push(1);
  nlst.push(100);
  nlst.print_list();
            std::cout<<nlst.gethead()->data_<<"\n";
  nlst.reverse_list();
  std::cout<<"\n";
  nlst.print_list();


  return 0;

}
