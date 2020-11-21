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
  scn++;
  node->id=scn;
  node->file=0;
  node->location=0;
  node->status=1;
  node->attributelist=NULL;
  node->attributelist=dll_new(node->attributelist, attribute_new(key, val));
  
  return node;
}

struct node_type * node_new_from_load(unsigned long long id, unsigned long long location){
  struct node_type * node=NULL;

  node=malloc(sizeof(struct node_type));
  node->id=id;
  node->file=0;
  node->location=location;
  node->status=2;
  node->attributelist=NULL;
  
  return node;
}
  
struct node_type * node_search(struct base_type * base, unsigned long long node_id){
  struct node_type *n;
  struct node_type * tmp_node;
  
  base->nodelist=first(base->nodelist);
  
  while(base->nodelist->next!=NULL){
    tmp_node=base->nodelist->payload;
    if(tmp_node->id==node_id){
      n=tmp_node;
    }
    base->nodelist=base->nodelist->next;
  }
  tmp_node=base->nodelist->payload;
  if(tmp_node->id==node_id){
    n=tmp_node;
  }
  
  return n;
}
