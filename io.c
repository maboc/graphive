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
