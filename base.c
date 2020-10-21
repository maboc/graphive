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
