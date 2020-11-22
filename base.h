#ifndef _BASE_
#define _BASE_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "dll.h"
#include "attribute.h"
#include "output.h"

extern struct dll * bases;
extern unsigned long long scn;

/*
Base

Field                        Data Type  memory  disk
type                               int             +
file                               int       +
location        unsigned long long int       +
id                                 int       +     +
status                             int       +     +
node list                        * dll       +
attribute list                   * dll       +
*/

struct base_type{
  int file;
  unsigned long long location;
  int id;
  int status;
  struct dll * nodelist;
  struct dll * attributelist;
};

struct base_type * base_new(char *);
struct base_type * base_new_from_load(int, unsigned long long);
struct base_type * base_find(int);
void base_show(struct base_type *, int);
void base_show_all(int);
void base_view(int, struct base_type *);

#endif
