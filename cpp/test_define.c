#include <stdio.h>

/*
 * Demonstration of struct uses with address space
 */


struct devregs{
   unsigned short  csr;    /* control & status */
   unsigned short  data;   /* data port */
};

#define DEVADDR ( (struct devregs *) 0xffff0004)

int main () 
{
   unsigned devno = 1;

   struct devregs* dvp = DEVADDR +  devno;

   printf(" devregs has value\t %d\n", dvp);

   return 0;
}
