#ifndef _NETWORK_
#define _NETWORK_

#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "logger.h"
#include "receiver.h"

extern int stoppenmaar;
extern struct config_struct * cfg;

void listener();


#endif
