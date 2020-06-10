#ifndef _CONFIG_
#define _CONFIG_

struct config_struct {
  int port;
  char * log;
  int startup_delay;
  char * data_dir;

  /*
Deze komen misschine later wel terug
  char * base_file;
  char * node_file;
  char * attr_file;
  char * rela_file;
  */
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct config_struct * cfg;

int config_read();

#endif
