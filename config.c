#include "config.h"

int config_read(){
  FILE * fp;
  char line[255];
  char * p;
  char * p2;
  int r=0;
  char * param;
  char * value;

  printf("Configuring\n");
  
  fp=fopen("graphive.cfg", "r");
  if(fp==NULL){
    printf("No config file found\r\n");
    r=3;
  }
  else{
    cfg=malloc(sizeof(struct config_struct));
    bzero(cfg, sizeof(struct config_struct));

    bzero(&line, 255);
    while(fgets(line, sizeof(line), fp)){

      /*split the line in a parameter and a value*/
      p=strstr(line, ":");
      if(p==NULL){
	printf("config_read : problem in line : %s (no :)\n", line);
	r=4;
      } else {
	param=malloc(p-line);
	param=strncpy(param, line, p-line);

	p2=strstr(line, "\n");
	if (p2==NULL){
	  printf("config_read : problem in line : %s (no newline)\n", line);
	  r=5;
	} else {
	  value=malloc(p2-p);
	  bzero(value, sizeof(value));
	  value=strncpy(value, p+1, p2-p-1);
	  
	  printf("Param : %s value : %s ", param, value);

	  if (strncmp(param,"port", strlen(param))==0){
	    cfg->port=atoi(value);
	    printf(" : Stored as a integer\n");
	  } else if (strncmp(param, "startup_delay", strlen(param))==0){
	    printf(" : Stored as a integer\n");
	    cfg->startup_delay=atoi(value);
	  } else if(strncmp(param, "log", strlen(param))==0){
	    cfg->log=malloc(strlen(value)+1);
	    bzero(cfg->log, strlen(value)+1);
	    cfg->log=strncpy(cfg->log, value, strlen(value));
	    printf(" : Stored as a string\n");
	  } else if(strncmp(param, "data_dir", strlen(param))==0){
	    cfg->data_dir=malloc(strlen(value)+1);
	    bzero(cfg->data_dir, strlen(value)+1);
	    cfg->data_dir=strncpy(cfg->data_dir, value, strlen(value));
	    printf(" : Stored as a string\n");
	    /*	  } else if(strncmp(param, "base_file", strlen(param))==0){
            cfg->base_file=malloc(strlen(value)+1);
            bzero(cfg->base_file, strlen(value)+1);
            cfg->base_file=strncpy(cfg->base_file, value, strlen(value));
            printf(" : Stored as a string\n");
          }else if(strncmp(param, "node_file", strlen(param))==0){
            cfg->node_file=malloc(strlen(value)+1);
            bzero(cfg->node_file, strlen(value)+1);
            cfg->node_file=strncpy(cfg->node_file, value, strlen(value));
            printf(" : Stored as a string\n");
          }else if(strncmp(param, "attr_file", strlen(param))==0){
            cfg->attr_file=malloc(strlen(value)+1);
            bzero(cfg->attr_file, strlen(value)+1);
            cfg->attr_file=strncpy(cfg->attr_file, value, strlen(value));
            printf(" : Stored as a string\n");
          }else if(strncmp(param, "rela_file", strlen(param))==0){
            cfg->rela_file=malloc(strlen(value)+1);
            bzero(cfg->rela_file, strlen(value)+1);
            cfg->rela_file=strncpy(cfg->rela_file, value, strlen(value));
            printf(" : Stored as a string\n");
	    */
          }
	  
	  else {
	    printf(" : No clue what to do\n");
	  }
	  free(param);
	  free(value);
	  bzero(&line, 255);
	}
      }
    }
    
    fclose(fp);
  }
  
  return r;
}
      
