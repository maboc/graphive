#ifndef _LISTENER_
#define _LISTENER_

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "logging.h"
#include "handler.h"

extern int goon;

void * listener(void *);


#endif
