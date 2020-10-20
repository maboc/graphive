#ifndef _BASE_
#define _BASE

#include <stddef.h>
#include <stdlib.h>
#include "dll.h"
#include "attribute.h"

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

#endif