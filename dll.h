#ifndef _DLL_
#define _DLL_

#include <stddef.h>

struct dll {
  struct dll * prev;
  struct dll * next;
  void * payload;
};



#endif
