#include "graphive.h"

int main(int argc, char * argv)
{
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
    /*THe child in action*/
    logger("This is the child speaking\n");
  } else {
    /*This is the parent .... exiting*/
    printf("This is the parent speaking. pid of the child : %i\n", pid);    
  }
  
  return rc;

}