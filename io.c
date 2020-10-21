#include "io.h"

int load(char * filename){

  return 0;
}

int create_file(char * filename){
  int rc=0;
  FILE * fp;
  int n;
  char * buffer;
  
  logger("Create file");
  logger(filename);

  buffer=malloc(1024*1024);
  bzero(buffer,1024*1024);
		
  fp=fopen("graphive.dat", "a+");
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
  n=fwrite(buffer, 1024*1024, 1, fp);
  fflush(fp);
  /* 1 omdat ik fwrite anders niet goed aand e praat krijg */
  if(n!=1) rc=6;
  
  bzero(buffer,1024*1024);
  sprintf(buffer, "%i", n);
  logger(buffer);

  free(buffer);
  
  return rc;
}

int regular_file(char * filename){
  struct stat buffer;
  int rc=0;
  int s;
  
  s=stat(filename, &buffer);
  if(S_ISREG(buffer.st_mode)){
    logger("File is a regular file");
    logger(filename);
  } else {
    logger("File is not a regular file");
    logger(filename);
    rc=6;
  }

  return rc;
}

int file_exists(char * filename){
  struct stat buffer;
  int rc = 0;
  int s;
  
  s=stat(filename, &buffer);
  if (s!=0){
    logger("I can not detemine stat for file");
    logger(filename);
    rc=4;
  } else {
    logger("I can determine stat for filename");
    logger(filename);
  }

  return rc;
}
  
/* when starting the initial load there are no bases yet...so no need to supply NULL*/
int initial_load(){
  int rc;
  FILE * fp;

  rc=file_exists("graphive.dat");
  if (rc==0){
    rc=regular_file("graphive.dat");
    if(rc==0){
      rc=load("graphive.dat");
    }
  } else {
    rc=create_file("graphive.dat");
  }

  return rc; 
}

int write_base_attributes(struct base_type * base){
  struct attribute_type * attr;
  char * tmp;
  

  base->attributelist=first(base_attributelist);
  while (base->attribute_list->next!=NULL){
    attr=base->attribute_list->payload;
    
  }
  
}

int write_base(struct base_type * base){
  char * tmp;

  tmp=malloc(100);
  sprintf(tmp, "Write base : %i", base->id);
  logger(tmp);
  free(tmp);

  write_base_attributes(base->attributelist);
  
  return 0;
}

int write_bases(struct dll * bases){
  local_bases=first(local_bases);
  while(local_bases->next!=NULL){
    rc=write_base(local_bases->payload);
    local_bases=local_bases->next;
  }
  rc=write_base(local_bases->payload);

  return 0;
}

void * data_writer(void * data_in){
  struct dll * local_bases;
  int rc=0;
  sleep(30);  
  logger("Starting data_writer thread");
  sleep(60);
  while(goon==0){
    logger("data_writer sweep");
    local_bases=bases;

    if (local_bases!=NULL){ //only process the data if there are actual bases
      write_bases(local_bases);
    } else {
      logger("No bases yet to write");
    }
    
    sleep(60);//just for now....every minute we sweep through the data
  }
  return NULL;
}
