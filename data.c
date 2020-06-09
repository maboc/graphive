#include "data.h"

int data_load(){
  int r=0;
  struct stat dir_stat;
  char * tmp;
  char * base;
  
  /* does the data_dir exists */
  tmp=malloc(1000);
  bzero(tmp, 1000);
  if(stat(cfg->data_dir, &dir_stat)){
    sprintf(tmp, "Something wend wrong with the data_dir (%s)\n", cfg->data_dir);
    logger(tmp);
    free(tmp);
    r=1;
  } else {
    if (S_ISDIR(dir_stat.st_mode)){  
      sprintf(tmp, "Datadir (%s) is an actual directory\n", cfg->data_dir);
      logger(tmp);
      
      /* Check whether the basefile exists */
      base=malloc(strlen(cfg->data_dir)+strlen(cfg->base_file)+2); /* +2 voor een slash en een afluitende 0 */
      bzero(base, strlen(cfg->data_dir)+strlen(cfg->base_file)+2);
      base=strncpy(base, cfg->data_dir, strlen(cfg->data_dir));
      base=strcat(base, "/");
      base=strcat(base, cfg->base_file);
      
      sprintf(tmp, "Base file %s\n", base);
      logger(tmp);
      free(tmp);
      
      if(stat(base, &dir_stat)==0){
	if(S_ISREG(dir_stat.st_mode)){
	  sprintf(tmp, "Base file (%s) exists and is a regular file\n", base);
	  logger(tmp);
	  free(tmp);
	  
	} else {
	  sprintf(tmp, "Base file (%s) problem (it's not a regular file)\n", base);
	  logger(tmp);
	  free(tmp);
	  r=6;
	}
      } else {
	logger("Something wend wrong checking the basefile\n");
	logger("It probably does not exist...we assume a new install\n");
      }
    } else {
      sprintf(tmp, "Datadir (%s) is not an actual directory\n", cfg->data_dir);
      logger(tmp);
      r=2;
      free(tmp);
    }
  }
  
  return r;
}
