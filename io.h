#ifndef _IO_
#define _IO_

#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include "logging.h"
#include "base.h"

extern struct dll * bases;
extern int goon;

int initial_load();
void * data_writer(void *);

#endif
