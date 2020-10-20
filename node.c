#include "node.h"

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

struct node_type * node_new(char * key, char * val){
  struct node_type * node=NULL;

  node=malloc(sizeof(struct node_type));
  node->id+=scn;
  node->file=0;
  node->location=0;
  node->status=1;
  node->attributeslist=NULL;
  node->attributeslist=dll_new(node->attributeslist, attribute_new(key, val));
  
  return node;
}
