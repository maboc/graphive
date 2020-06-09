#ifndef _COMMAND_
#define _COMMAND_

#include <string.h>
#include "dll.h"
#include "stddef.h"

char * command_arg(struct dll *, int);
struct dll * command_pre_parse(struct dll *, char *);

#endif
