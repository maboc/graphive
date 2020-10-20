#include "graphive.h"

struct dll * bases;
unsigned long long int scn=0;

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
    if(rc==0){
      rc=logger("Starting Initial Load");
      rc=initial_load(bases);
      if(rc==0){
	logger("Initial Load succeeded");
	/*for startup testing create a base*/
	rc=startup_creation();
      } else {
	logger("Initial Load did not nucceed...exiting");
    }
    } else {
      /*This is the parent .... exiting*/
      printf("This is the parent speaking. pid of the child : %i\n", pid);
    }
  }
  
  return rc;
}
