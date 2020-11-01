#ifndef _NODE_
#define _NODE_

#include "base.h"

/*
  -------------------------------------------------------------
  Node
  
  Field                       Data Type Memory Disk
  type                              int           +
  base                              int           +
  id             unsigned long long int      +    +
  file                              int      +
  location       unsigned long long int      +
  status                            int      +    +
  attribute list                  * dll      +
*/

struct node_type{
  unsigned long long id;
  int file;
  unsigned long long location;
  int status;
  struct dll * attributelist;
};

struct node_type * node_new(char *, char *);

#endif
