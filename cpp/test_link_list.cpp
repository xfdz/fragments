#include <iostream>
#include "node1.h"

using namespace main_savitch_s;

int main() {

   node *n;

   double num = 48;
  
   n = new node();

   n->set_data(num);

   std::cout << n->data() << std::endl;
 
   return 0;
}
