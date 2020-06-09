#include "attribute.h"

struct attribute_struct * attribute_new(char * key, char * value){
  struct attribute_struct * a;

  a=malloc(sizeof(struct attribute_struct));
  a->id=++system_counter;
  a->storage_id=-1;
  a->key=malloc(strlen(key));
  bzero(a->key, strlen(key));
  a->key=strncpy(a->key, key, strlen(key));
  a->value=malloc(strlen(value));
  bzero(a->value, strlen(value));
  a->value=strncpy(a->value, value, strlen(value));

  return a;
}

void attributes_display(int s, struct dll * attributes){
  if(attributes!=NULL){
    attributes=dll_first(attributes);
    while(attributes->next!=NULL){
      attribute_display(s, attributes->payload);
      attributes=attributes->next;
    }
    attribute_display(s, attributes->payload);
  }
}

void attribute_display(int s, struct attribute_struct * attribute){
  char * tmp;
  
  if(attribute!=NULL){
    tmp=malloc(1000);
    sprintf(tmp, "%s : %s\n", attribute->key, attribute->value);
    output_line(s, tmp);
    free(tmp);
  }
}
