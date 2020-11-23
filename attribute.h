#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dll.h"
#include "output.h"

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
struct attribute_type * attribute_new_from_load(unsigned long long, char *, char *, unsigned long long);
void attribute_show(int, struct attribute_type *);
void attributes_show(int, struct dll *);

#endif
