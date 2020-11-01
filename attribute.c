#include "attribute.h"

/*
-------------------------------------------------------------
Attribute Node

Field                       Data Type Memory Disk
type                              int           +
base_node_rel_type                int           +  0 - base 1 -node 2- relation
base                              int           +
node               unsigned long long           +
relation           unsigned long long           +  0 als node_rel_type=node 
id                 unsigned long long      +    +
key length                        int           +
key                            string      +    +
value length                      int           +
value                          string      +    +
file                              int      +
location           unsigned long long      +
status                            int      +    +
*/

struct attribute_type * attribute_new(char * key, char * val){
  struct attribute_type * attr;

  attr=malloc(sizeof(struct attribute_type));
  attr->id=scn++;
  attr->key=malloc(strlen(key)+1);//+1 om een \0 te kunnen toevoegen
  bzero(attr->key, strlen(key)+1);
  attr->key=strncpy(attr->key, key, strlen(key)+1);
  attr->val=malloc(strlen(val)+1);//+1 om een \0 te kunnen toevoegen
  bzero(attr->val, strlen(val)+1);
  attr->val=strncpy(attr->val, val, strlen(val)+1);
  attr->file=0;
  attr->location=0;
  attr->status=1;
  
  return attr;
}
