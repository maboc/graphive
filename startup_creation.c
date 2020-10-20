#include "startup_creation.h"

int startup_creation(){
  int rc;
  
  logger("Startup Creation");

  if(bases!=NULL){
    bases=dll_new(bases, base_new("base_base"));
    
  } else {
    rc=7;
    logger("Strange : there allready is a base...doing nothing");
  }
  
  return rc;
}
