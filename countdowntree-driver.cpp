#include <iostream>
#include <cstdlib>
using namespace std;

#include "countdowntree.h"

int main()
{
  //Test a large degenerate tree
  CountdownTree degen;
  for (int i = 0; i < 1024; i++)
    degen.insert(i);
  //degen.countdown();  degen.countdown();
  //degen.countdown();  degen.countdown();
  degen.validate();
  cout << degen << endl;

  //Consider adding more test cases...

  return 0;
}