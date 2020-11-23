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
struct node_type * node_new_from_load(unsigned long long, unsigned long long);
struct node_type * node_search(struct base_type *, unsigned long long);
void node_show(int, struct node_type *);
void nodes_show(int, struct dll *);
#endif
