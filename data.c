#include "data.h"

int data_load(){
  int r=0;
  struct stat dir_stat;
  char * tmp;
  char * base;
  
  /* does the data_dir exists */
  tmp=malloc(1000);
  bzero(tmp, 1000);
  if(stat(cfg->data_dir, &dir_stat)==0){
    /*stat is OK...conitune*/
    if (S_ISDIR(dir_stat.st_mode)!=0){
      bzero(tmp, 1000);
      sprintf(tmp, "Datadir (%s) is an actual directory\n", cfg->data_dir);
      logger(tmp);
      
      /*THe cofig item cfg->data_dir is actually a dir...continue*/
      
      /* Check whether the basefile exists */
      base=malloc(strlen(cfg->data_dir)+strlen("/base.dat")+1); /* +1 voor een afluitende 0 */
      bzero(base, strlen(cfg->data_dir)+strlen("/base.dat")+1);
      base=strncpy(base, cfg->data_dir, strlen(cfg->data_dir));
      base=strcat(base, "/");
      base=strcat(base, "base.dat");
      
      bzero(tmp, 1000);
      sprintf(tmp, "Base file %s\n", base);
      logger(tmp);
      
      if(stat(base, &dir_stat)==0){
	/* Apperantly the stat operation succeeded */
	
	if(S_ISREG(dir_stat.st_mode)!=0){
	  bzero(tmp, 1000);
	  sprintf(tmp, "Base file (%s) exists and is a regular file\n", base);
	  logger(tmp);
	  
	  
	} else {
	  bzero(tmp, 1000);
	  sprintf(tmp, "Apperently base file (%s) is not a regular file\n", base);
	  logger(tmp);

	  r=6;
	}
      } else {
	bzero(tmp, 1000);
	sprintf(tmp, "stat basefile(%s) wend belly up\n", base);
	logger(tmp);
	
	r=7;
      }
    } else {
      bzero(tmp, 1000);
      sprintf(tmp, "Datadir (%s) is _not_ an actual directory\n", cfg->data_dir);
      logger(tmp);
      
      r=2;
    }
  } else {
    bzero(tmp, 1000);
    sprintf(tmp, "Stat datadir (%s) wend wrong\n", cfg->data_dir);
    logger(tmp);

    r=1;
  }
  return r;  
}

void * data_handler(void * data_in){
  while (stoppenmaar==0){
    logger("data_handler run\n");
    /* iterate over the bases */
    if(bases!=NULL){
      bases=dll_first(bases);
      while(bases->next!=NULL){
	struct base_struct * b = bases->payload;
      }
      struct base_struct * b = bases->payload;
    } else {
      logger("data_handler : No bases yet\n");
    }
    
    sleep(10);
  }
  
  return NULL;
}
