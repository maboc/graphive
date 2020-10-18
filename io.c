#include "io.h"

int load(char * filename){

  return 0;
}

int create_file(char * filename){
  int rc;
  FILE * fp;
  int n;
  
  rc=logger("Create file");
  rc=logger(filename);

  fp=fopen("graphive.dat", "a+");
  n=fwrite(NULL, 1, 1024*1024, fp);
  
  return 0;
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
