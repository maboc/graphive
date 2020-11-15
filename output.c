#include "output.h"

void output_line(int s, char * message){
  int l;

  l=strlen(message);
  write(s, message, l);
}

