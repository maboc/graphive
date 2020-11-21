#ifndef _RECEIVER_
#define _RECEIVER_

#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "logging.h"
#include "output.h"
#include "parser.h"
#include "base.h"
#include "node.h"

extern int goon;
extern struct dll * bases;

void * handler(void *);

#endif
