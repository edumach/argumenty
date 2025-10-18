/**************/
/*  soucet.c  */
/**************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a;
    int b;
    
    a = atoi(argv[1]); /* prvni argument */
    b = atoi(argv[2]); /* druhy argument */

    printf("%d + %d = %d\n", a, b, a + b);
    
    return 0;
}
