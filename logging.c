#include "logging.h"

int logger(char * message){
  int rc=0;
  FILE * fp;
  time_t nu;
  struct tm * nu_echt;
  char * nu_string;
  char * totaal;
  
  fp=fopen("graphive.log","a");
  if(fp==NULL){
    /* problems opening/creating the logfile */
    rc=2;
  } else {
    nu=time(NULL);
    nu_echt=localtime(&nu);
    
    totaal=malloc(100);
    int tmp;
    tmp=sprintf(totaal, "%i %i %i %i %i %i : %s\n", nu_echt->tm_year+1900,nu_echt->tm_mon+1, nu_echt->tm_mday, nu_echt->tm_hour, nu_echt->tm_min, nu_echt->tm_sec, message);
    
    tmp=fprintf(fp, "%s", totaal);

    free(totaal);
    rc=(tmp<=0)?3:0;
    fclose(fp);
  }

  return rc;
}
