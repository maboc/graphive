#include "graphive.h"

struct config_struct *cfg;
struct dll * bases=NULL;
int stoppenmaar;
long system_counter;

int main(int argc, char ** argv){
  int r;
  int pid;
  
  printf("Starting graphive\n\r");
  r=config_read();
  if (r==0){
    printf("All messages will continue in the logfile (%s)\n", cfg->log);
    
    logger("Starting data load\n");
    r=data_load();
    if (r==0){
      logger("Data succesfully loaded\n");
      
      logger("Move to the background\nSee you there\n");
      
      pid=fork();
      if(pid==0){
	/* this is the child fork */
	sleep(cfg->startup_delay);
	logger("The child has started\n");

	/* fire up the network */
	listener();
      } else {
	/* this is the parent */
	printf("Child process : %i\n", pid);
      }
      
    } else {
      logger("Data is NOT succesfully loaded...stop here\n");
    }
  } else {
    printf("No Config...stop now\n");
  }
  
  return r;
}
