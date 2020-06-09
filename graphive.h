#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include "dll.h"
#include "config.h"
#include "logger.h"
#include "network.h"
#include "data.h"

extern struct config_struct * cfg;
extern struct dll * bases;
extern int stoppenmaar;
extern long system_counter;
