#ifndef _BASE_
#define _BASE_

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "dll.h"
#include "output.h"
#include "attribute.h"

struct base_struct {
  long id;
  char * storage_file;
  long storage_pos;
  int mode;
  struct dll * attributes;
};

extern long system_counter;

struct base_struct * base_new();
int base_display(int, struct base_struct *);

#endif 
