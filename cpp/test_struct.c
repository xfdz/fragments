#include <stdio.h>

struct x {
   int a;
};

#define X ( (struct x *) 500);

int main()
{

   struct x *a = X;

   printf(" your number %d:", a->a);
   return 0;

}
