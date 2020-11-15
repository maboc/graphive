#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "logging.h"
#include "dll.h"
#include "io.h"
#include "startup_creation.h"
#include "listener.h"

extern struct dll * bases;
extern unsigned long long int scn;
extern int goon;
