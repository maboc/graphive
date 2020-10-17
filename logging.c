#include "logging.h"

int logger(char * message){
  int rc=0;
  FILE * fp;
  time_t nu;
  char * nu_string;
  
  fp=fopen("graphive.log","a");
  if(fp==NULL){
    /* problems opening/creating the logfile */
    rc=2;
  } else {
    nu=time(NULL);
    nu_string=ctime(&nu);
    
    int tmp;
    tmp=fprintf(fp, "%s : %s\n", nu_string, message);
    rc=(tmp<0)?3:0;
  }

  return rc;
}
