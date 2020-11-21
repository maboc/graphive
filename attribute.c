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

struct attribute_type * attribute_new_from_load(unsigned long long id, char * k, char * v, unsigned long long location){
  struct attribute_type * attr;

  attr=malloc(sizeof(struct attribute_type));
  attr->id=id;
  attr->key=malloc(strlen(k)+1);//+1 om een \0 te kunnen toevoegen
  bzero(attr->key, strlen(k)+1);
  attr->key=strncpy(attr->key, k, strlen(k)+1);
  attr->val=malloc(strlen(v)+1);//+1 om een \0 te kunnen toevoegen
  bzero(attr->val, strlen(v)+1);
  attr->val=strncpy(attr->val, v, strlen(v)+1);
  attr->file=0;
  attr->location=location;
  attr->status=2;
  
  return attr;
}  

void attribute_show(int s, struct attribute_type * attr){
  char * tmp;

  tmp=malloc(1000);
  bzero(tmp, 1000);
  sprintf(tmp, "ID : %i Attribute key : %s Attribute value : %s\r\n", attr->id, attr->key, attr->val);
  output_line(s, tmp);
  free(tmp);
  
  return;
}

void attributes_show(int s, struct dll * list){
  if(list!=NULL){
    list=first(list);

    while(list->next!=NULL){
      attribute_show(s, list->payload);
      list=list->next;
    }
    attribute_show(s,list->payload);
  }
  
  return;
}
