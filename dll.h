#ifndef _DLL_
#define _DLL_

#include <stddef.h>
#include <stdlib.h>

extern long system_counter;

struct dll {
  struct dll * prev;
  struct dll * next;
  void * payload;
};

struct dll * dll_first(struct dll *);
struct dll * dll_last(struct dll *);
int dll_count(struct dll *);
struct dll * dll_new(struct dll *);

#endif 
