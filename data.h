#ifndef _DATA_
#define _DATA_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "config.h"
#include "logger.h"
#include "dll.h"

extern struct config_struct * cfg;
extern int stoppenmaar;
extern struct dll * bases;

int data_load();
void * data_handler(void *);

#endif
