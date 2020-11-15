#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  
  output_line(s, "graphive....welcome\n");
  
  return NULL;
}
