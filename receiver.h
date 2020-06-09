#ifndef _RECEIVER_
#define _RECEIVER_

#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include "parser.h"
#include "base.h"
#include "attribute.h"
#include "output.h"
#include "string.h"

extern int stoppenmaar;
extern struct dll * bases;

void *receive(void *);


#endif
