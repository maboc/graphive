#ifndef _ATTR_
#define _ATTR_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "output.h"
#include "dll.h"

extern long system_counter;

struct attribute_struct {
  long id;
  long storage_id;
  char * key;
  char * value;
};

struct attribute_struct * attribute_new(char *, char *);
void attributes_display(int, struct dll *);
void attribute_display(int, struct attribute_struct *);

#endif
