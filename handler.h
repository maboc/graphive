#ifndef _RECEIVER_
#define _RECEIVER_

#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "logging.h"
#include "output.h"

extern int stoppenmaar;
extern struct dll * bases;

void * handler(void *);


#endif
