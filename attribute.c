#include "attribute.h"

/*
-------------------------------------------------------------
Attribute Node

Field                       Data Type Memory Disk
type                              int           +
node_rel_type                     int           +  0 - node 1 - relation
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
  attr->id+=scn;  
  return attr;
}
