#include "base.h"


struct base_type * base_new(char * name){
  struct base_type * base;

  base = malloc(sizeof(struct base_type));
  base->file=-1;
  base->location=-1;
  scn++;
  base->id=scn;
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

void base_show(struct base_type * base, int s){
  char * tmp;
  
  output_line(s, "Base\r\n");
  tmp=malloc(1000);
  bzero(tmp, 1000);

  sprintf(tmp, "ID         : %i\r\n", base->id);
  output_line(s, tmp);
  bzero(tmp, 1000);
  sprintf(tmp, "Nodes      : %i\r\n", dll_count(base->nodelist));
  output_line(s, tmp);
  bzero(tmp,1000);
  sprintf(tmp, "Attributes : %i\r\n", dll_count(base->attributelist));
  output_line(s, tmp);
  attributes_show(s, base->attributelist);
  
  bzero(tmp,1000);
  sprintf(tmp, "\r\n");
  output_line(s, tmp);
  
  free(tmp);
	  
  return;
}

void base_show_all(int s){
  struct dll * local_bases;

  local_bases=bases;
  local_bases=first(local_bases);

  while(local_bases->next!=NULL){
    base_show(local_bases->payload, s);
    local_bases=local_bases->next;
  }
  base_show(local_bases->payload,s);

  return;
}

void base_view(int s, struct base_type * base){
  base_show(base, s);
  nodes_show(s, base->nodelist);
  
  return;
}
