#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_

#include <stdlib.h>

struct attribute_type {
  unsigned long long id;
  char * key;
  char * val;
  int file;
  unsigned long long location;
  int status;
};

extern unsigned long long scn;

struct attribute_type * attribute_new(char *, char *);

#endif
