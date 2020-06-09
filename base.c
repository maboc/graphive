#include "base.h"

struct base_struct * base_new(){
  struct base_struct * b;
  
  b=malloc(sizeof(struct base_struct));
  b->id=++system_counter;
  b->attributes=NULL;
  b->mode=0;
  b->storage_pos=-1;
  b->storage_file=0;
  
  return b;
}

int base_display(int s, struct base_struct * base){
  char * tmp;

  tmp=malloc(1000);
  bzero(tmp, 1000);
  sprintf(tmp, "ID           : %i\n",base->id);
  output_line(s, tmp);
  bzero(tmp, 1000);
  sprintf(tmp, "Storage File : %s\n", base->storage_file);
  output_line(s, tmp);
  bzero(tmp, 1000);
  sprintf(tmp, "Storage Pos  : %i\n", base->storage_pos);
  output_line(s, tmp);
  free(tmp);

  attributes_display(s, base->attributes);

  return 0;
}
