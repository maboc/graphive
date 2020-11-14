#include "base.h"


struct base_type * base_new(char * name){
  struct base_type * base;

  base = malloc(sizeof(struct base_type));
  base->file=-1;
  base->location=-1;
  base->id=scn++;
  base->status=1;
  base->attributelist=NULL;
  base->nodelist=NULL;

  base->attributelist=dll_new(base->attributelist, attribute_new("Name", name));
  
  return base;
}

struct base_type * base_new_from_load(int id, unsigned long long location){
  struct base_type * base;
  
  base = malloc(sizeof(struct base_type));
  base->id=id;
  base->status=2;
  base->file=0;
  base->location=location;
  base->attributelist=NULL;
  base->nodelist=NULL;
    
  return base;
}

struct base_type * base_find(int base_id){
  struct base_type * b=NULL;
  struct base_type * temp_base=NULL;
  
  bases=first(bases);
  while (bases->next!=NULL){
    temp_base=bases->payload;
    if (temp_base->id==base_id){
      b=temp_base;
    }
    bases=bases->next;
  }
  temp_base=bases->payload;
  if (temp_base->id==base_id){
    b=temp_base;
  }

  return b;
}
