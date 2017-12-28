#include <stdlib.h>
#include <stdio.h>

int main(
)


{
  int * array;
  array = (int *)malloc(sizeof(
			       int) * 10);
  printf(
	 "addr = %p\n",
	 array);
  // free(array);  <== cause memory leak!
  free(
       array
       );
  return                     100;
}
