#include "logger.h"

void logger(char * message){
  FILE * fp;
  fp=fopen(cfg->log,"a");

  fputs(message, fp);

  fclose(fp);
}
