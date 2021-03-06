#include "graphive.h"

struct dll * bases=NULL;
unsigned long long int scn=0;
int goon=0; //0 - go on 1 - quit

int main(int argc, char * argv)
{

  struct dll * bases=NULL;
  
  int rc=0;
  pid_t pid=0;
  
  printf("Graphive\n");
  printf("Starting Instance\n");

  printf("Moving to the background\n");

  pid=fork();
  if (pid==-1){
    /*Something wend terribly wrong forking the process*/
    rc=1;
    /*This is the running child*/
  } else if (pid==0){
    /*The child in action*/
    rc=logger("This is the child speaking\n");
    sleep(3);
    if(rc==0){
      rc=logger("Starting Initial Load");
      rc=initial_load(bases);
      if(rc==0){
	logger("Initial Load succeeded");
	if(bases==NULL){
	  /*for startup testing create a base*/
	  rc=startup_creation();
	}
	
	/* let's startup the write process*/
		
	pthread_t data_writer_thread;
	rc=pthread_create(&data_writer_thread, NULL, data_writer, NULL);
	
	char * tmp;
	tmp=malloc(100);
	sprintf(tmp, "Spawning data writer thread : rc : %i", rc);
	logger(tmp);
	free(tmp);

	pthread_t listener_thread;
	rc=pthread_create(&listener_thread, NULL, listener,NULL);
	
	tmp=malloc(100);
	sprintf(tmp, "Spawning data listener thread : rc : %i", rc);
	logger(tmp);
	free(tmp);
	
	pthread_join(data_writer_thread, NULL);
      } else {
	logger("Initial Load did not succeed...exiting");
      }
    } else {
      /*This is the parent .... exiting*/
      printf("This is the parent speaking. pid of the child : %i\n", pid);
    }
  }
  
  return rc;
}
