#include "startup_creation.h"

int startup_creation(){
  int rc;
  struct base_type * base;
  
  logger("Startup Creation");

  if(bases==NULL){
    base=base_new("base_base");
    base->nodelist=dll_new(base->nodelist, node_new("name", "node_1"));
    bases=dll_new(bases, base);
    
  } else {
    rc=7;
    logger("Strange : there allready is a base...doing nothing");
  }
  
  return rc;
}
