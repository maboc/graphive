#ifndef _DLL_
#define _DLL_

#include <stddef.h>
#include <stdlib.h>

struct dll {
  struct dll * prev;
  struct dll * next;
  void * payload;
};

struct dll * first(struct dll *);
struct dll * last(struct dll *);
struct dll * dll_new(struct dll *, void *);

#endif
